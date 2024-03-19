#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QHostAddress>

class server_manager : public QMainWindow
{
    Q_OBJECT
public:
    server_manager(QHostAddress ip = QHostAddress::LocalHost, int port = 12345, QWidget *parent = nullptr);
    server_manager(QTcpSocket *client, QWidget *parent = nullptr);
    void disconnect_all_clients();

    void connect_to_server();
    void send_text(QString text);
    void send_name(QString name);
    void send_is_typing();

    QString name() const;

private:
    QWidget *central_widget;

    QTcpServer *_server;
    chat_protocol *_protocol;

    QList<QTcpSocket *> _clients;
    QTcpSocket *_socket;

    QHostAddress _ip;
    int _port;

signals:
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void disconnected();

    void text_message_received(QString message);
    void name_changed(QString name);
    void is_typing_received();

private slots:
    void new_connection();
    void client_disconnected();

    void ready_read();
};
