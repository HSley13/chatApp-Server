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

private: // variables
    QWidget *central_widget;

    QTcpServer *_server;

    QList<QTcpSocket *> _clients;

private: // functions
    void setup_server(int port);

signals:
    void new_client_connected(QTcpSocket *client);
    void client_disconnected(QTcpSocket *client);

private slots:
    void new_client_connection();
    void on_client_disconnected();
};