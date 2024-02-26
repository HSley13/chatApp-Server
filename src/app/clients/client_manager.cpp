#include "client_window.h"
#include <QTcpSocket>
#include <QHostAddress>

client_manager::client_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent), _ip(ip), _port(port)
{
    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &client_manager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &client_manager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &client_manager::ready_read);
}
void client_manager::connect_to_server()
{
    _socket->connectToHost(_ip, _port);
}

void client_manager::send_message(QString message)
{
    _socket->write(message.toUtf8());
}

void client_manager::ready_read()
{
    auto data = _socket->readAll();

    emit data_receive(data);
}