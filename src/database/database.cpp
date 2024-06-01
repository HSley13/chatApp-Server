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

        if (!result->next())
            return std::string();

        std::string hashed_password = result->getString("hashed_password");

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
        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_int_distribution<int> distribution(1024, 49151);

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT INTO accounts (phone_number, first_name, last_name, port) VALUES(?, ?, ?, ?);"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setString(2, first_name);
        prepared_statement->setString(3, last_name);
        prepared_statement->setInt(4, distribution(generator));

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

QVector<QString> Account::retrieve_conversation(sql::Connection *connection, const int &conversation_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT sender_ID, receiver_ID, content, date_time, message_type FROM messages WHERE conversation_ID = ? ORDER BY date_time;"));
        prepared_statement->setInt(1, conversation_ID);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QVector<QString> messages;

        while (result->next())
        {
            QString message = QString("%1/%2/%3/%4/%5")
                                  .arg(result->getString("sender_ID").c_str())
                                  .arg(result->getString("receiver_ID").c_str())
                                  .arg(result->getString("content").c_str())
                                  .arg(result->getString("date_time").c_str())
                                  .arg(result->getString("message_type").c_str());

            messages.push_back(message);
        }

        return messages;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_conversation() ---> SQL ERROR: " << e.what() << std::endl;
        return QVector<QString>();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return QVector<QString>();
    }
}

QHash<int, QHash<QString, int>> Account::retrieve_friend_list(sql::Connection *connection, const int &phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT CASE WHEN participant1_ID = ? THEN participant2 ELSE participant1 END AS other_participant, CASE WHEN participant1_ID = ? THEN participant2_ID ELSE participant1_ID END AS other_participant_ID, conversation_ID FROM conversations WHERE participant1_ID = ? OR participant2_ID = ?;"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setInt(2, phone_number);
        prepared_statement->setInt(3, phone_number);
        prepared_statement->setInt(4, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<int, QHash<QString, int>> friend_list_pack;

        while (result->next())
        {
            std::string participant2 = result->getString("other_participant");
            int participant2_ID = result->getInt("other_participant_ID");

            QHash<QString, int> friend_list;
            friend_list.insert(QString::fromStdString(participant2), participant2_ID);

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
        QString date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time));

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO messages (conversation_ID, sender_ID, receiver_ID, content, date_time) VALUES (?,?,?,?,?);"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setInt(2, sender_ID);
        prepared_statement->setInt(3, receiver_ID);
        prepared_statement->setString(4, content);
        prepared_statement->setString(5, date_time.toStdString());

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

        if (!result->next())
            return QString();

        std::string name = result->getString("alias");

        return QString::fromStdString(name);
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

void Account::save_binary_data(sql::Connection *connection, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const std::string &file_name, const char *file_data, const int &file_size, const std::string &type, const std::string &time)
{
    try
    {
        std::istringstream blob_stream(std::string(file_data, file_size));

        QString date_time = QString("%1 %2").arg(QDate::currentDate().toString("yyyy-MM-dd"), QString::fromStdString(time));

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO binary_data (conversation_ID, sender_ID, receiver_ID, file_name, file_data, data_type, date_time) VALUES (?,?,?,?,?,?,?);"));
        prepared_statement->setInt(1, conversation_ID);
        prepared_statement->setInt(2, sender_ID);
        prepared_statement->setInt(3, receiver_ID);
        prepared_statement->setString(4, file_name);
        prepared_statement->setBlob(5, &blob_stream);
        prepared_statement->setString(6, type);
        prepared_statement->setString(7, date_time.toStdString());

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

QHash<QString, QByteArray> Account::retrieve_binary_data(sql::Connection *connection, const int &conversation_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT date_time, file_data FROM binary_data WHERE conversation_ID = ? ORDER BY date_time;"));
        prepared_statement->setInt(1, conversation_ID);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<QString, QByteArray> binary_data;

        while (result->next())
        {
            QString date_time = result->getString("date_time").c_str();

            std::istream *file_stream = result->getBlob("file_data");

            QByteArray file_data = QByteArray::fromStdString(std::string(std::istreambuf_iterator<char>(*file_stream), {}));

            binary_data.insert(date_time, file_data);
        }

        return binary_data;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "retrieve_binary_data() ---> SQL ERROR: " << e.what() << std::endl;
        return QHash<QString, QByteArray>();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return QHash<QString, QByteArray>();
    }
}

void Account::delete_message(sql::Connection *connection, const int &conversation_ID, const std::string &time)
{
    try
    {
        QString date_time;

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