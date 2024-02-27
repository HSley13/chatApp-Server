#include "server_manager.h"

server_manager::server_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent), _ip(ip), _port(port)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &server_manager::new_connection);

    _server->listen(_ip, _port);
}

void server_manager::client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    _clients.removeOne(client);

    emit new_client_disconnected(client);
}

void server_manager::new_connection()
{
    QTcpSocket *client = _server->nextPendingConnection();

    _clients << client;

    int id = _clients.length();

    client->setProperty("id", id);
    connect(client, &QTcpSocket::disconnected, this, &server_manager::client_disconnected);

    emit new_client_connected(client);
}

void server_manager::disconnect_all_clients()
{
    for (QTcpSocket *client : _clients)
        client->disconnectFromHost();
}