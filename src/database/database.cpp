#include "database.h"
#include <random>

sql::Connection *connection_setup(connection_details *ID)
{
    try
    {
        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = ID->server;
        connection_properties["port"] = ID->port;
        connection_properties["userName"] = ID->user;
        connection_properties["schema"] = ID->schema;
        connection_properties["password"] = ID->password;

        sql::mysql::MySQL_Driver *driver;
        driver = sql::mysql::get_driver_instance();

        sql::Connection *connection = driver->connect(connection_properties);

        return connection;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "connection_setup() --> SQL ERROR: " << e.what() << std::endl;

        return nullptr;
    }
}

std::string Security::generate_random_salt(std::size_t len)
{
    try
    {
        std::string valid_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#&?!~^-$%*+";

        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_int_distribution<> distribution(0, valid_chars.size() - 1);

        std::string salt;
        for (size_t i = 0; i < len; i++)
            salt.push_back(valid_chars[distribution(generator)]);

        return salt;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return std::string();
    }
}

std::string Security::hashing_password(const std::string &password)
{
    try
    {
        const size_t SALT_LENGTH = 32;

        std::string salt = generate_random_salt(SALT_LENGTH);

        const uint32_t t_cost = 2;
        const uint32_t m_cost = 32;
        const uint32_t parallelism = 1;
        const uint32_t hash_length = 32;

        std::string hash;
        hash.resize(hash_length);

        int result = argon2_hash(t_cost, m_cost, parallelism, password.c_str(), password.length(), salt.c_str(), salt.length(), &hash[0], hash.length(), NULL, 0, Argon2_id, ARGON2_VERSION_NUMBER);

        if (result != ARGON2_OK)
        {
            std::cout << "Error Hashing Password" << std::endl;

            return std::string();
        }

        std::string hashed_password = salt + hash;

        return hashed_password;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return std::string();
    }
}

bool Security::verifying_password(const std::string &password, const std::string &hashed_password)
{
    try
    {
        const uint32_t t_cost = 2;
        const uint32_t m_cost = 32;
        const uint32_t parallelism = 1;
        const uint32_t hash_length = 32;

        const size_t SALT_LENGTH = hashed_password.length() - hash_length;

        std::string hash;
        hash.resize(hash_length);

        int result = argon2_hash(t_cost, m_cost, parallelism, password.c_str(), password.length(), hashed_password.c_str(), SALT_LENGTH, &hash[0], hash.length(), NULL, 0, Argon2_id, ARGON2_VERSION_NUMBER);

        if (result != ARGON2_OK)
        {
            std::cout << "Error Verifying Password" << std::endl;

            return false;
        }

        return !hashed_password.substr(SALT_LENGTH, hash_length).compare(hash);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return false;
    }
}

std::string Security::retrieve_hashed_password(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prep_statement(connection->prepareStatement("SELECT hashed_password FROM password_security WHERE phone_number = ?"));
        prep_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prep_statement->executeQuery());

        std::string hashed_password = std::string();

        if (result->next())
            hashed_password = result->getString("hashed_password");

        return hashed_password;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_hashed_password() ---> SQL ERROR: " << e.what() << std::endl;

        return std::string();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return std::string();
    }
}

void Account::create_account(sql::Connection *connection, const int &phone_number, const std::string &first_name, const std::string &last_name, const std::string &secret_question, const std::string &secret_answer, const std::string &password)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT INTO accounts (phone_number, first_name, last_name) VALUES(?, ?, ?);"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setString(2, first_name);
        prepared_statement->setString(3, last_name);

        prepared_statement->executeUpdate();

        std::string hashed_password = Security::hashing_password(password);

        prepared_statement = std::unique_ptr<sql::PreparedStatement>(connection->prepareStatement("INSERT INTO password_security VALUES(?, ?, ?, ?);"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setString(2, hashed_password);
        prepared_statement->setString(3, secret_question);
        prepared_statement->setString(4, secret_answer);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "create_account() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

QStringList Account::retrieve_conversation(sql::Connection *connection, const int &conversation_ID, const int &client_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT CASE WHEN participant1_ID = ? THEN last_message_read1 ELSE last_message_read2 END AS last_message_read, CASE WHEN participant2_ID = ? THEN last_message_read2 ELSE last_message_read1 END AS last_message_read FROM conversations WHERE participant1_ID = ? OR participant2_ID = ?;"));
        prepared_statement->setInt(1, client_ID);
        prepared_statement->setInt(2, client_ID);
        prepared_statement->setInt(3, client_ID);
        prepared_statement->setInt(4, client_ID);
        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QString last_message_read = QString();
        if (result->next())
            last_message_read = result->getString("last_message_read").c_str();

        std::unique_ptr<sql::PreparedStatement> prepared_statement_2(connection->prepareStatement("SELECT sender_ID, receiver_ID, content, date_time, message_type FROM messages WHERE conversation_ID = ? ORDER BY date_time;"));
        prepared_statement_2->setInt(1, conversation_ID);
        std::unique_ptr<sql::ResultSet> result_2(prepared_statement_2->executeQuery());

        QStringList messages = QStringList();
        int count = 0;
        while (result_2->next())
        {
            QString date_time = result_2->getString("date_time").c_str();

            QDateTime dt1 = QDateTime::fromString(date_time, "yyyy-MM-dd HH:mm:ss");
            QDateTime dt2 = QDateTime::fromString(last_message_read, "yyyy-MM-dd HH:mm:ss");

            if (dt1.secsTo(dt2) < 0)
                count++;

            QString message = QString("%1/%2/%3/%4/%5/%6")
                                  .arg(result_2->getString("sender_ID").c_str())
                                  .arg(result_2->getString("receiver_ID").c_str())
                                  .arg(result_2->getString("content").c_str())
                                  .arg(date_time)
                                  .arg(result_2->getString("message_type").c_str())
                                  .arg(QString::number(count));

            messages << message;
        }

        return messages;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_conversation() ---> SQL ERROR: " << e.what() << std::endl;
        return QStringList();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return QStringList();
    }
}

QHash<int, QHash<QString, QString>> Account::retrieve_friend_list(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT CASE WHEN participant1_ID = ? THEN participant2 ELSE participant1 END AS other_participant, CASE WHEN participant1_ID = ? THEN participant2_ID ELSE participant1_ID END AS other_participant_ID, conversation_ID FROM conversations WHERE participant1_ID = ? OR participant2_ID = ?;"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setInt(2, phone_number);
        prepared_statement->setInt(3, phone_number);
        prepared_statement->setInt(4, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<int, QHash<QString, QString>> friend_list_pack = {};

        while (result->next())
        {
            QHash<QString, QString> friend_list = {};

            QString participant2_ID = QString::number(result->getInt("other_participant_ID"));
            QString participant2 = result->getString("other_participant").c_str();

            friend_list.insert(participant2_ID, participant2);

            int conversation_ID = result->getInt("conversation_ID");

            friend_list_pack.insert(conversation_ID, friend_list);
        }

        return friend_list_pack;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_friend_list() ---> SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

void Account::save_text_message(sql::Connection *connection, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const std::string &content, const std::string &time)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO messages (conversation_ID, sender_ID, receiver_ID, content, date_time) VALUES (?,?,?,?,?);"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setInt(2, sender_ID);
        prepared_statement->setInt(3, receiver_ID);
        prepared_statement->setString(4, content);
        prepared_statement->setString(5, time);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "save_text_message() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::create_conversation(sql::Connection *connection, const int &conversation_ID, const std::string &participant1, const int &participant1_ID, const std::string &participant2, const int &participant2_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO conversations (conversation_ID, participant1, participant1_ID, participant2, participant2_ID) VALUES (?,?,?,?,?);"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setString(2, participant1);
        prepared_statement->setInt(3, participant1_ID);
        prepared_statement->setString(4, participant2);
        prepared_statement->setInt(5, participant2_ID);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "create_conversation() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

QString Account::retrieve_alias(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT alias FROM accounts WHERE phone_number = ?;"));
        prepared_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QString name = QString();

        if (result->next())
            name = result->getString("alias").c_str();

        return name;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_name_and_port() ---> SQL ERROR: " << e.what() << std::endl;
        return QString();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return QString();
    }
}

void Account::update_alias(sql::Connection *connection, const int &phone_number, const std::string &name)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("UPDATE accounts SET alias = ? WHERE phone_number = ?;"));
        prepared_statement->setString(1, name);
        prepared_statement->setInt(2, phone_number);

        prepared_statement->executeUpdate();

        std::unique_ptr<sql::PreparedStatement> prepared_statement_conversation(connection->prepareStatement("UPDATE conversations SET participant1 = CASE WHEN participant1_ID = ? THEN ? ELSE participant1 END, participant2 = CASE WHEN participant2_ID = ? THEN ? ELSE participant2 END WHERE participant1_ID = ? OR participant2_ID = ?;"));
        prepared_statement_conversation->setInt(1, phone_number);
        prepared_statement_conversation->setString(2, name);
        prepared_statement_conversation->setInt(3, phone_number);
        prepared_statement_conversation->setString(4, name);
        prepared_statement_conversation->setInt(5, phone_number);
        prepared_statement_conversation->setInt(6, phone_number);

        prepared_statement_conversation->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "update_alias() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::save_binary_data(sql::Connection *connection, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const std::string &data_name, const char *data_data, const int &data_size, const std::string &type, const std::string &time)
{
    try
    {
        std::istringstream blob_stream(std::string(data_data, data_size));

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO binary_data (conversation_ID, sender_ID, receiver_ID, file_name, file_data, data_type, date_time) VALUES (?,?,?,?,?,?,?);"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setInt(2, sender_ID);
        prepared_statement->setInt(3, receiver_ID);
        prepared_statement->setString(4, data_name);
        prepared_statement->setBlob(5, &blob_stream);
        prepared_statement->setString(6, type);
        prepared_statement->setString(7, time);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "save_binary_data() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

QHash<QString, QByteArray> Account::retrieve_binary_data(sql::Connection *connection, const int &conversation_ID, const std::string &date_time)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT file_data, data_type FROM binary_data WHERE conversation_ID = ? AND date_time = ?;"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setString(2, date_time);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<QString, QByteArray> binary_data = {};

        if (result->next())
        {

            std::istream *file_stream = result->getBlob("file_data");
            QByteArray file_data = QByteArray::fromStdString(std::string(std::istreambuf_iterator<char>(*file_stream), {}));

            QString data_type = result->getString("data_type").c_str();

            binary_data.insert(data_type, file_data);
        }

        return binary_data;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_binary_data() ---> SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

void Account::delete_message(sql::Connection *connection, const int &conversation_ID, const std::string &time)
{
    try
    {
        QString date_time = QString();

        (time.length() < 10) ? date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time)) : date_time = QString::fromStdString(time);

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("DELETE FROM messages WHERE conversation_ID = ? AND date_time = ?;"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setString(2, date_time.toStdString());

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "delete_message() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::delete_group_message(sql::Connection *connection, const int &group_ID, const std::string &time)
{
    try
    {
        QString date_time = QString();

        (time.length() < 10) ? date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time)) : date_time = QString::fromStdString(time);

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("DELETE FROM group_messages WHERE group_ID = ? AND date_time = ?;"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setString(2, date_time.toStdString());

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "delete_group_message() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::add_to_group(sql::Connection *connection, const int &group_ID, const std::string &group_name, const int &phone_number, const std::string &user_role)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT INTO group_memberships (group_ID, group_name, participant_ID, user_role) VALUES (?,?,?,?);"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setString(2, group_name);
        prepared_statement->setInt(3, phone_number);
        prepared_statement->setString(4, user_role);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "add_to_group() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

QStringList Account::retrieve_group_members(sql::Connection *connection, const int &group_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT participant_ID FROM group_memberships WHERE group_ID = ?;"));
        prepared_statement->setInt(1, group_ID);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QStringList members = QStringList();

        while (result->next())
        {
            QString member = QString::number(result->getInt("participant_ID"));

            members << member;
        }

        return members;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "add_to_group() ---> SQL ERROR: " << e.what() << std::endl;
        return QStringList();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return QStringList();
    }
}

QHash<int, QHash<int, QString>> Account::retrieve_group_list(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT group_ID, group_name FROM group_memberships WHERE participant_ID = ?;"));
        prepared_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<int, QHash<int, QString>> group_list = {};

        while (result->next())
        {
            int group_ID = result->getInt("group_ID");
            QString group_name = result->getString("group_name").c_str();

            std::unique_ptr<sql::PreparedStatement> prepared_statement_1(connection->prepareStatement("SELECT participant_ID FROM group_memberships WHERE user_role = 'admin' AND group_ID = ?;"));
            prepared_statement_1->setInt(1, group_ID);

            std::unique_ptr<sql::ResultSet> result_2(prepared_statement_1->executeQuery());

            QHash<int, QString> group_name_and_adm;
            while (result_2->next())
            {
                int admin = result_2->getInt("participant_ID");
                group_name_and_adm.insert(admin, group_name);
            }

            group_list.insert(group_ID, group_name_and_adm);
        }

        return group_list;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_friend_list() ---> SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

void Account::save_group_text_message(sql::Connection *connection, const int &group_ID, const std::string &sender, const std::string &content, const std::string &time)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO group_messages (group_ID, sender, content, date_time) VALUES (?,?,?,?);"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setString(2, sender);
        prepared_statement->setString(3, content);
        prepared_statement->setString(4, time);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "save_group_text_message() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::save_group_binary_data(sql::Connection *connection, const int &group_ID, const std::string &sender, const std::string &data_name, const char *data_data, const int &data_size, const std::string &type, const std::string &time)
{
    try
    {
        std::istringstream blob_stream(std::string(data_data, data_size));

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO group_binary_data (group_ID, sender, file_name, file_data, data_type, date_time) VALUES (?,?,?,?,?,?);"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setString(2, sender);
        prepared_statement->setString(3, data_name);
        prepared_statement->setBlob(4, &blob_stream);
        prepared_statement->setString(5, type);
        prepared_statement->setString(6, time);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "save_group_binary_data() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

QStringList Account::retrieve_group_conversation(sql::Connection *connection, const int &group_ID, const int &client_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT last_message_read FROM group_memberships WHERE group_ID = ? AND participant_ID = ?;"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setInt(2, client_ID);
        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QString last_message_read = QString();
        if (result->next())
            last_message_read = result->getString("last_message_read").c_str();

        std::unique_ptr<sql::PreparedStatement> prepared_statement_2(connection->prepareStatement("SELECT sender, content, date_time, message_type FROM group_messages WHERE group_ID = ? ORDER BY date_time;"));
        prepared_statement_2->setInt(1, group_ID);
        std::unique_ptr<sql::ResultSet> result_2(prepared_statement_2->executeQuery());

        QStringList messages = QStringList();
        int count = 0;
        while (result_2->next())
        {
            QString date_time = result_2->getString("date_time").c_str();

            QDateTime dt1 = QDateTime::fromString(date_time, "yyyy-MM-dd HH:mm:ss");
            QDateTime dt2 = QDateTime::fromString(last_message_read, "yyyy-MM-dd HH:mm:ss");

            if (dt1.secsTo(dt2) < 0)
                count++;

            QString message = QString("%1/%2/%3/%4/%5")
                                  .arg(result_2->getString("sender").c_str())
                                  .arg(result_2->getString("content").c_str())
                                  .arg(date_time)
                                  .arg(result_2->getString("message_type").c_str())
                                  .arg(QString::number(count));

            messages << message;
        }

        return messages;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_group_conversation() ---> SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

QHash<QString, QByteArray> Account::retrieve_group_binary_data(sql::Connection *connection, const int &group_ID, const std::string &date_time)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT file_data, data_type FROM group_binary_data WHERE group_ID = ? AND date_time = ?;"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setString(2, date_time);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<QString, QByteArray> binary_data = {};

        if (result->next())
        {
            std::istream *file_stream = result->getBlob("file_data");
            QByteArray file_data = QByteArray::fromStdString(std::string(std::istreambuf_iterator<char>(*file_stream), {}));

            QString data_type = result->getString("data_type").c_str();

            binary_data.insert(data_type, file_data);
        }

        return binary_data;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_group_binary_data() ---> SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

void Account::remove_from_group(sql::Connection *connection, const int &group_ID, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("DELETE FROM group_memberships WHERE group_ID = ? AND participant_ID = ?;"));
        prepared_statement->setInt(1, group_ID);
        prepared_statement->setInt(2, phone_number);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "remove_to_group() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::delete_account(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("DELETE FROM accounts WHERE phone_number = ?;"));
        prepared_statement->setInt(1, phone_number);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "delete_account() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::update_last_message_read(sql::Connection *connection, const int &conversation_ID, const int &client_ID, const std::string &time)
{
    try
    {
        QString date_time = QString();

        (time.length() < 10) ? date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time)) : date_time = QString::fromStdString(time);

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("UPDATE conversations SET last_message_read1 = CASE WHEN participant1_ID = ? THEN ? ELSE last_message_read1 END, last_message_read2 = CASE WHEN participant2_ID = ? THEN ? ELSE last_message_read2 END WHERE conversation_ID = ? AND (participant1_ID = ? OR participant2_ID = ?) ;"));
        prepared_statement->setInt(1, client_ID);
        prepared_statement->setString(2, date_time.toStdString());
        prepared_statement->setInt(3, client_ID);
        prepared_statement->setString(4, date_time.toStdString());
        prepared_statement->setInt(5, conversation_ID);
        prepared_statement->setInt(6, client_ID);
        prepared_statement->setInt(7, client_ID);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "update_last_message_read() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::update_group_last_message_read(sql::Connection *connection, const int &group_ID, const int &client_ID, const std::string &time)
{
    try
    {
        QString date_time = QString();

        (time.length() < 10) ? date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time)) : date_time = QString::fromStdString(time);

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("UPDATE group_memberships SET last_message_read = ? WHERE group_ID = ? AND participant_ID = ?;"));
        prepared_statement->setString(1, date_time.toStdString());
        prepared_statement->setInt(2, group_ID);
        prepared_statement->setInt(3, client_ID);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "update_group_last_message_read() ---> SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}