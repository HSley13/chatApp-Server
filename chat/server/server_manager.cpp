#include "server_manager.h"
#include <QDir>
#include <QDateTime>

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
    _socket->write(_protocol->set_text_message(text));
}

void server_manager::send_name(QString name)
{
    _socket->write(_protocol->set_name_message(name));
}

void server_manager::send_is_typing()
{
    _socket->write(_protocol->set_is_typing_message());
}

void server_manager::send_init_sending_file(QString filename)
{
    _file_name = filename;
    _socket->write(_protocol->set_init_sending_file_message(filename));
}

void server_manager::send_accept_file()
{
    _socket->write(_protocol->set_accept_file_message());
}

void server_manager::send_reject_file()
{
    _socket->write(_protocol->set_reject_file_message());
}

void server_manager::send_file()
{
    _socket->write(_protocol->set_file_message(_file_name));
}

void server_manager::save_file()
{
    QDir *dir = new QDir();
    dir->mkdir(name());

    QString path = QString("%1/%2/%3_%4").arg(dir->canonicalPath(), name(), QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

    QFile *file = new QFile(path);

    if (file->open(QIODevice::WriteOnly))
    {
        file->write(_protocol->file_data());
        file->close();

        emit file_saved(path);
    }
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

    case chat_protocol::init_sending_file:
        emit init_receiving_file(_protocol->name(), _protocol->file_name(), _protocol->file_size());

        break;

    case chat_protocol::accept_sending_file:
        send_file();

        break;

    case chat_protocol::reject_sending_file:
        emit reject_receiving_file();

        break;

    case chat_protocol::send_file:
        save_file();

        break;

    default:
        break;
    }
}
