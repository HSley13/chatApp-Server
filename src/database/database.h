#pragma once

#include <iostream>
#include <string>
#include <random>
#include <stack>
#include <vector>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <argon2.h>

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>
#include <QWebSocket>
#include <QWebSocketServer>

class connection_details
{
public:
    std::string server, user, schema, password;
    int port;
};

sql::Connection *connection_setup(connection_details *ID);

class Security
{
public:
    static std ::string generate_random_salt(size_t len);

    static std ::string hashing_password(const std::string &password);

    static bool verifying_password(const std::string &password, const std::string &hashed_password);

    static std ::string retrieve_hashed_password(sql::Connection *connection, const int &account_number);
};

class Account
{
public:
    static void create_account(sql::Connection *connection, const int &phone_number, const std::string &first_name, const std::string &last_name, const std::string &secret_question, const std::string &secret_answer, const std::string &password);

    static void create_conversation(sql::Connection *connection, const int &conversation_ID, const std::string &participant1, const int &participant1_ID, const std::string &participant2, const int &participant2_ID);

    static QHash<int, QHash<QString, int>> retrieve_friend_list(sql::Connection *connection, const int &phone_number);

    static QString retrieve_alias(sql::Connection *connection, const int &phone_number);

    static void update_alias(sql::Connection *connection, const int &phone_number, const std::string &name);

    static void save_text_message(sql::Connection *connection, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const std::string &content, const std::string &time);

    static void save_binary_data(sql::Connection *connection, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const std::string &file_name, const char *file_data, const int &file_size, const std::string &type, const std::string &time);

    static QStringList retrieve_conversation(sql::Connection *connection, const int &conversation_ID);

    static QHash<QString, QByteArray> retrieve_binary_data(sql::Connection *connection, const int &conversation_ID, const std::string &date_time);

    static void delete_message(sql::Connection *connection, const int &conversation_ID, const std::string &time);

    static void add_to_group(sql::Connection *connection, const int &group_ID, const std::string &group_name, const int &phone_number, const std::string &user_role = std::string());

    static QStringList retrieve_group_members(sql::Connection *connection, const int &group_ID);

    static QHash<int, QHash<int, QString>> retrieve_group_list(sql::Connection *connection, const int &phone_number);

    static void save_group_text_message(sql::Connection *connection, const int &group_ID, const std::string &sender_ID, const std::string &content, const std::string &time);

    static void save_group_binary_data(sql::Connection *connection, const int &group_ID, const std::string &sender_ID, const std::string &file_name, const char *file_data, const int &file_size, const std::string &type, const std::string &time);

    static QStringList retrieve_group_conversation(sql::Connection *connection, const int &group_ID);

    static QHash<QString, QByteArray> retrieve_group_binary_data(sql::Connection *connection, const int &group_ID, const std::string &date_time);

    static void remove_from_group(sql::Connection *connection, const int &group_ID, const int &phone_number);

    static void delete_account(sql::Connection *connection, const int &phone_number);
};