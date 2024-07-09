#pragma once

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QtSql>
class connection_details
{
public:
    QString server, user, schema, password;
    int port;
};

QSqlDatabase connection_setup(const connection_details &details);
class Security
{
public:
    static QString generate_random_salt(std::size_t len);

    static QString hashing_password(const QString &password);

    static bool verifying_password(const QString &password, const QString &hashed_password);

    static QString retrieve_hashed_password(QSqlDatabase &db, const int &phone_number);
};

class Account
{
public:
    static void create_account(QSqlDatabase &db, const int &phone_number, const QString &first_name, const QString &last_name, const QString &secret_question, const QString &secret_answer, const QString &password);

    static void create_conversation(QSqlDatabase &db, const int &conversation_ID, const QString &participant1, const int &participant1_ID, const QString &participant2, const int &participant2_ID);

    static QHash<int, QHash<QString, QString>> retrieve_friend_list(QSqlDatabase &db, const int &phone_number);

    static QString retrieve_alias(QSqlDatabase &db, const int &phone_number);

    static void update_alias(QSqlDatabase &db, const int &phone_number, const QString &name);

    static void save_text_message(QSqlDatabase &db, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const QString &content, const QString &time);

    static void save_binary_data(QSqlDatabase &db, const int &conversation_ID, const int &sender_ID, const int &receiver_ID, const QString &data_name, const QByteArray &data_data, const QString &type, const QString &time);

    static QStringList retrieve_conversation(QSqlDatabase &db, const int &conversation_ID, const int &client_ID, const QString &timeZone_ID);

    static QHash<QString, QByteArray> retrieve_binary_data(QSqlDatabase &db, const int &conversation_ID, const QString &date_time);

    static void delete_message(QSqlDatabase &db, const int &conversation_ID, const QString &time);

    static void delete_group_message(QSqlDatabase &db, const int &group_ID, const QString &time);

    static void add_to_group(QSqlDatabase &db, const int &group_ID, const QString &group_name, const int &phone_number, const QString &user_role = QString());

    static QStringList retrieve_group_members(QSqlDatabase &db, const int &group_ID);

    static QHash<int, QHash<int, QString>> retrieve_group_list(QSqlDatabase &db, const int &phone_number);

    static void save_group_text_message(QSqlDatabase &db, const int &group_ID, const QString &sender_ID, const QString &content, const QString &time);

    static void save_group_binary_data(QSqlDatabase &db, const int &group_ID, const QString &sender_ID, const QString &data_name, const QByteArray &data_data, const QString &type, const QString &time);

    static QStringList retrieve_group_conversation(QSqlDatabase &db, const int &group_ID, const int &client_ID, const QString &timeZone_ID);

    static QHash<QString, QByteArray> retrieve_group_binary_data(QSqlDatabase &db, const int &group_ID, const QString &date_time);

    static void remove_from_group(QSqlDatabase &db, const int &group_ID, const int &phone_number);

    static void delete_account(QSqlDatabase &db, const int &phone_number);

    static void update_last_message_read(QSqlDatabase &db, const int &conversation_ID, const int &client_ID, const QString &time);

    static void update_group_last_message_read(QSqlDatabase &db, const int &conversation_ID, const int &client_ID, const QString &time);

    static QString UTC_to_timeZone(const QString &UTC_time, const QString &timeZone_ID);
};