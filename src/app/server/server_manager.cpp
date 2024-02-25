#include "server_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>

server_manager::server_manager(int port, QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    setup_server(port);
}

void server_manager::on_client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    int id = client->property("id").toInt();

    _clients.removeOne(client);

    emit client_disconnected(client);
}

void server_manager::new_client_connection()
{
    QTcpSocket *client = _server->nextPendingConnection();

    _clients << client;

    int id = _clients.length();

    client->setProperty("id", id);
    connect(client, &QTcpSocket::disconnected, this, &server_manager::on_client_disconnected);

    emit new_client_connected(client);
}

void server_manager::setup_server(int port)
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &server_manager::new_client_connection);

    _server->listen(QHostAddress::Any, port);
}
