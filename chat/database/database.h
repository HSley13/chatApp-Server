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

class connection_details
{
public:
    std::string server, user, schema, password;
    int port;
};

sql::Connection *connection_setup(connection_details *ID);