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

    static std ::string hashing_password(const std ::string password);

    static bool verifying_password(const std ::string password, const std ::string &hashed_password);

    static std ::string retrieve_hashed_password(sql ::Connection *connection, const int account_number);
};

class Account
{
public:
    static void create_account(sql::Connection *connection, const int phone_number, const std::string first_name, const std::string last_name, const std::string secret_question, const std::string secret_answer, const std::string &hash_password);
};