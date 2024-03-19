#include "server_manager.h"

server_manager::server_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent), _ip(ip), _port(port)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &server_manager::new_connection);

    _server->listen(_ip, _port);

    _socket = new QTcpSocket(this);
}

server_manager::server_manager(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    _protocol = new chat_protocol(this);

    connect(_socket, &QTcpSocket::connected, this, &server_manager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &server_manager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &server_manager::ready_read);
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

void server_manager::client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    _clients.removeOne(client);

    emit new_client_disconnected(client);
}

void server_manager::disconnect_all_clients()
{
    for (QTcpSocket *client : _clients)
        client->disconnectFromHost();
}

void server_manager::send_text(QString text)
{
    _socket->write(_protocol->text_message(text));
}

void server_manager::send_name(QString name)
{
    _socket->write(_protocol->set_name_message(name));
}

void server_manager::send_is_typing()
{
    _socket->write(_protocol->is_typing_message());
}

QString server_manager::name() const
{
    int id = _socket->property("id").toInt();

    QString name = _protocol->name().length() > 0 ? _protocol->name() : QString("Client %1").arg(id);

    return name;
}

void server_manager::ready_read()
{
    QByteArray data = _socket->readAll();

    _protocol->load_data(data);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        emit text_message_received(_protocol->message());

        break;

    case chat_protocol::set_name:
        emit name_changed(name());

        break;

    case chat_protocol::is_typing:
        emit is_typing_received();

        break;

    default:
        break;
    }
}
