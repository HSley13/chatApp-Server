#pragma once

#include "chat_protocol.h"
#include "database.h"

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class client_manager : public QMainWindow
{
    Q_OBJECT
public:
    client_manager(sql::Connection *db_connection, QWidget *parent = nullptr);

    static sql::Connection *_db_connection;

    void send_text(QString sender, QString receiver, QString text);
    void send_name(QString name);
    void send_is_typing(QString sender, QString receiver);

    void send_init_sending_file(QString filename);
    void send_accept_file();
    void send_reject_file();

    void send_init_sending_file_client(QString sender, QString receiver, QString filename);
    void send_accept_file_client(QString receiver);
    void send_reject_file_client(QString sender, QString receiver);

    void send_file();
    void send_file_client(int port_transfer);

    void save_file();
    void save_file_client(QString sender);

private:
    static QTcpSocket *_socket;
    QHostAddress _ip = QHostAddress::LocalHost;
    int _port = 12345;

    static chat_protocol *_protocol;

    static QTcpServer *_file_server;
    QTcpSocket *_file_socket;

    QString _file_name;
    QString _file_name_client;

signals:
    void text_message_received(QString sender, QString message);
    void is_typing_received(QString sender);

    void init_receiving_file(QString file_name, qint64 file_size);
    void reject_receiving_file();

    void init_receiving_file_client(QString sender, QString file_name, qint64 file_size);
    void reject_receiving_file_client(QString sender);

    void file_saved(QString path);
    void file_client_saved(QString path);

    void client_connected(QString client_name);
    void clients_list(QString my_name, QHash<QString, QString> other_clients);
    void client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name);

    void socket_disconnected();

    void file_accepted();
    void file_accepted_client();

private slots:
    void on_disconnected();

    void on_ready_read();

    void file_connect();

    void on_new_connection();
};