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
        std::cerr << "SQL ERROR: " << e.what() << std::endl;

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

        return "";
    }
}

std::string Security::hashing_password(const std::string password)
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

            return "";
        }

        std::string hashed_password = salt + hash;

        return hashed_password;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return "";
    }
}

bool Security::verifying_password(const std::string password, const std::string &hashed_password)
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

std::string Security::retrieve_hashed_password(sql::Connection *connection, const int phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prep_statement(connection->prepareStatement("SELECT hashed_password FROM password_security WHERE phone_number = ?"));
        prep_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prep_statement->executeQuery());

        if (!result->next())
        {
            QMessageBox::warning(nullptr, "Warning!", "Error Retrieving hash password! The Account entered doesn't exist in our database, Check and try again");

            return "";
        }

        std::string hashed_password = result->getString("hashed_password");

        return hashed_password;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;

        return "";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        return "";
    }
}

void Account::create_account(sql::Connection *connection, const int phone_number, const std::string first_name, const std::string last_name, const std::string secret_question, const std::string secret_answer, const std::string &hashed_password)
{
    try
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist(9999, std::numeric_limits<int>::max());

        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT INTO accounts VALUES(?, ?, ?, ?);"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setString(2, first_name);
        prepared_statement->setString(3, last_name);
        prepared_statement->setInt(4, dist(gen));

        prepared_statement->executeUpdate();

        prepared_statement = std::unique_ptr<sql::PreparedStatement>(connection->prepareStatement("INSERT INTO password_security VALUES(?, ?, ?, ?);"));
        prepared_statement->setInt(1, phone_number);
        prepared_statement->setString(2, hashed_password);
        prepared_statement->setString(3, secret_question);
        prepared_statement->setString(4, secret_answer);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<std::string> Account::retrieve_conversation(sql::Connection *connection, const int conversation_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT sender_ID, receiver_ID, content, date_time FROM message WHERE conversation_id = ? ORDER BY date_time;"));
        prepared_statement->setInt(1, conversation_ID);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        std::vector<std::string> messages;

        while (result->next())
        {
            std::string message;
            message = result->getString("sender_ID") + "/" + result->getString("receiver_ID") + "/" + result->getString("content") + "/" + result->getString("date_time");

            messages.push_back(message);
        }

        return messages;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

QHash<QString, int> Account::retrieve_friend_list(sql::Connection *connection, const int phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT participant1, participant2, participant1_ID, participant1_ID FROM conversations WHERE phone_number = ? ;"));
        prepared_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        QHash<QString, int> friend_list;

        while (result->next())
        {
            std::string participant1 = result->getString("participant1");
            int participant1_ID = result->getInt("participant1_ID");

            std::string participant2 = result->getString("participant2");
            int participant2_ID = result->getInt("participant2_ID");

            if (participant1_ID == phone_number)
                friend_list.insert(QString::fromStdString(participant2), participant2_ID);
            else
                friend_list.insert(QString::fromStdString(participant1), participant1_ID);
        }

        return friend_list;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
        return {};
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return {};
    }
}

void Account::save_message(sql::Connection *connection, const int sender, const int receiver, const std::string content)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT INTO messages (sender_ID, receiver_ID, content) VALUES (?,?,?);"));
        prepared_statement->setInt(1, sender);
        prepared_statement->setInt(2, receiver);
        prepared_statement->setString(3, content);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Account::create_conversation(sql::Connection *connection, std::string participant1, const int participant1_ID, std::string participant2, const int participant2_ID)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("INSERT IGNORE INTO conversations (participant1, participant1_ID, participant2, participant2_ID) VALUES (?,?,?,?);"));
        prepared_statement->setString(1, participant1);
        prepared_statement->setInt(2, participant1_ID);
        prepared_statement->setString(3, participant2);
        prepared_statement->setInt(4, participant2_ID);

        prepared_statement->executeUpdate();
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::string Account::retrieve_full_name_and_port(sql::Connection *connection, const int phone_number)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT first_name, last_name, port FROM accounts WHERE phone_number = ?;"));
        prepared_statement->setInt(1, phone_number);

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());

        if (!result->next())
            QMessageBox::warning(nullptr, "Phone Number XXX", "The entered Phone Number doesn't exist in our database, Check and try again");

        std::string name = result->getString("first_name") + " " + result->getString("last_name") + "/" + std::to_string(result->getInt("port"));

        return name;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
        return "";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return "";
    }
}

int Account::allocate_port(sql::Connection *connection)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> prepared_statement(connection->prepareStatement("SELECT port FROM port_pool;"));

        std::unique_ptr<sql::ResultSet> result(prepared_statement->executeQuery());
        if (!result->next())
        {
            std::cerr << "No available port in the pool." << std::endl;
            return 0;
        }

        int port = result->getInt("port");

        prepared_statement = std::unique_ptr<sql::PreparedStatement>(connection->prepareStatement("UPDATE port_pool SET port = ?;"));
        prepared_statement->setInt(1, port - 1);

        prepared_statement->executeUpdate();

        return port;
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQL ERROR: " << e.what() << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}