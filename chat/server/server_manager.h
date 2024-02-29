#pragma once

#include "server_chat_window.h"
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
    void disconnect_all_clients();

private:
    QWidget *central_widget;

    QTcpServer *_server;

    QList<QTcpSocket *> _clients;
    server_chat_window *_chat;

    QHostAddress _ip;
    int _port;

signals:
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    // void set_name_received(QString name);

private slots:
    void new_connection();
    void client_disconnected();
};