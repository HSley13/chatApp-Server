#include "client_manager.h"

client_manager::client_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent), _ip(ip), _port(port)
{
    _central_widget = new QWidget();
    setCentralWidget(_central_widget);

    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &client_manager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &client_manager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &client_manager::ready_read);

    _protocol = new chat_protocol();
}

void client_manager::connect_to_server()
{
    _socket->connectToHost(_ip, _port);
}

void client_manager::send_text(QString text)
{
    _socket->write(_protocol->set_text_message(text));
}

void client_manager::send_name(QString name)
{
    _socket->write(_protocol->set_name_message(name));
}

void client_manager::send_is_typing()
{
    _socket->write(_protocol->set_is_typing_message());
}

void client_manager::ready_read()
{
    QByteArray data = _socket->readAll();
    _protocol->load_data(data);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        emit text_message_received(_protocol->message());

        break;

    case chat_protocol::is_typing:
        emit is_typing_received();

        break;

    default:
        break;
    }
}