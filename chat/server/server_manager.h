#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QHostAddress>
#include <QMap>

class server_manager : public QMainWindow
{
    Q_OBJECT
public:
    server_manager(QHostAddress ip = QHostAddress::LocalHost, int port = 12345, QWidget *parent = nullptr);
    server_manager(QTcpSocket *client, QWidget *parent = nullptr);

    void connect_to_server();
    void disconnect_from_host();
    void disconnect_all_clients();

    void is_typing_for_other_clients(QString sender, QString receiver);

    void send_text(QString text);
    void send_is_typing(QString sender);

    void send_init_sending_file(QString filename);
    void send_accept_file();
    void send_reject_file();

    QString name() const;

    void update_name(QTcpSocket *client, QString old_name, QString new_name);

    void notify_other_clients(QString old_name, QString client_name);

    QMap<QString, QTcpSocket *> _clients; // I made it public cause I nedd an object within the server_main_window's destructor to access it and call delete on all clients'pointer

    static QMap<QString, QString> _names;

private:
    QWidget *central_widget;

    QTcpServer *_server;
    chat_protocol *_protocol;

    QTcpSocket *_socket;

    QString _file_name;

    QHostAddress _ip;
    int _port;

    void send_file();
    void save_file();

signals:
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void disconnected();

    void text_message_received(QString sender, QString receiver, QString message);
    void client_name_changed(QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void reject_receiving_file();

    void file_saved(QString path);

private slots:
    void new_connection();
    void on_client_disconnected();

    void on_ready_read();

public slots:
    void on_text_for_other_clients(QString sender, QString receiver, QString message);
};
