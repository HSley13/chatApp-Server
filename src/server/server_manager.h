#pragma once

#include "chat_protocol.h"
#include "database.h"
class server_manager : public QMainWindow
{
    Q_OBJECT
public:
    server_manager(sql::Connection *db_connection, QWidget *parent = nullptr);
    server_manager(QWebSocket *client, QWidget *parent = nullptr);

    static sql::Connection *_db_connection;

    void disconnect_from_host();
    void disconnect_all_clients();

    void is_typing_for_other_clients(QString sender, QString receiver);

    void send_text(QString text, QString time);
    void send_is_typing(QString sender);

    void notify_other_clients(QString old_name, QString client_name);

    void init_send_file_received(QString sender, QString sender_ID, QString receiver, QString file_name, qint64 file_size);
    void file_accepted(QString sender, QString receiver);
    void file_rejected(QString sender, QString receiver);
    void file_received(QString sender, QString receiver, QString file_name, QByteArray file_data, QString time);

    QString name() const;

    static QHash<QString, QWebSocket *> _clients;
    static QHash<QString, QString> _names;

    void create_conversation(int conversation_ID, QString participant1, int participant1_ID, QString participant2, int participant2_ID);
    void save_conversation_message(int conversation_ID, QString sender, QString receiver, QString content, QString time);
    void lookup_friend(QString ID);

    void audio_received(QString sender, QString receiver, QString audio_name, QByteArray audio_data, QString time);
    void save_data(int conversation_ID, QString sender, QString receiver, QString file_name, QByteArray file_data, QString data_type, QString time);

    void sign_up(QString phone_number, QString first_name, QString last_name, QString password, QString secret_question, QString secret_answer);

    void login_request(QString phone_number, QString password);

    void delete_message(const int conversation_ID, const QString &sender, const QString &receiver, const QString &time);

private:
    QWidget *central_widget;

    QWebSocketServer *_server;
    chat_protocol *_protocol;

    QWebSocket *_socket;

    QString _file_name;

    QHostAddress _ip = QHostAddress::LocalHost;
    int _port = 12345;

signals:
    void new_client_connected(QWebSocket *client);
    void new_client_disconnected(QWebSocket *client);

    void text_message_received(QString message, QString time);
    void client_name_changed(QString original_name, QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void after_login(QString old_name, QString name);

private slots:
    void on_new_connection();
    void on_client_disconnected();

    void on_binary_message_received(const QByteArray &message);

    void message_received(QString sender, QString receiver, QString message, QString time);
};