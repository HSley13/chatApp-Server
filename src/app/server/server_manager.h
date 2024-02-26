#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class server_manager : public QMainWindow
{
    Q_OBJECT

public:
    server_manager(int port = 4500, QWidget *parent = nullptr);
    void disconnect_all_clients();

private: // variables
    QWidget *central_widget;

    QTcpServer *_server;

    QList<QTcpSocket *> _clients;

private: // functions
signals:
    void new_client_connected(QTcpSocket *client);
    void client_disconnected(QTcpSocket *client);

private slots:
    void new_client_connection();
    void on_client_disconnected();
};