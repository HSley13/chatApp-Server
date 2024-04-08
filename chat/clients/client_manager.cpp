#include "client_manager.h"
#include <QFileDialog>
#include <QFile>
#include <QStringList>

client_manager::client_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent), _ip(ip), _port(port)
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(_ip, _port);
    connect(_socket, &QTcpSocket::connected, this, &client_manager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &client_manager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &client_manager::ready_read);

    _protocol = new chat_protocol(this);
}

client_manager::client_manager(QString destinator, QWidget *parent)
    : QMainWindow(parent)
{
}

void client_manager::send_text(QString sender, QString receiver, QString text)
{
    _socket->write(_protocol->set_text_message(sender, receiver, text));
}

void client_manager::send_name(QString name)
{
    _socket->write(_protocol->set_name_message(name));
}

void client_manager::send_is_typing()
{
    _socket->write(_protocol->set_is_typing_message());
}

void client_manager::send_init_sending_file(QString filename)
{
    _file_name = filename;
    _socket->write(_protocol->set_init_sending_file_message(filename));
}

void client_manager::send_accept_file()
{
    _socket->write(_protocol->set_accept_file_message());
}

void client_manager::send_reject_file()
{
    _socket->write(_protocol->set_reject_file_message());
}

void client_manager::send_file()
{
    _socket->write(_protocol->set_file_message(_file_name));
}

void client_manager::save_file()
{
    QDir dir;
    dir.mkdir("Server");
    dir.setPath("./");

    QString path = QString("%1/%2/%3_%4").arg(dir.canonicalPath(), "Server", QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

    QFile file(path);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(_protocol->file_data());
        file.close();

        emit file_saved(path);
    }
}

void client_manager::ready_read()
{
    QByteArray data = _socket->readAll();
    _protocol->load_data(data);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        emit text_message_received(_protocol->sender(), _protocol->message());
        qDebug() << "client_manager-->emitting text_message_received()";

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

    case chat_protocol::new_client:
        emit client_connected(_protocol->client_name());
        qDebug() << "client_manager-->emitting client_connected()";

        break;

    case chat_protocol::connection_ACK:
        emit connection_ACK(_protocol->my_name(), _protocol->clients_name());

        break;

    case chat_protocol::client_new_name:
        emit client_name_changed(_protocol->old_name(), _protocol->client_name());

        break;

    case chat_protocol::client_disconnected:
        emit client_disconnected(_protocol->client_name());

        break;

    default:
        break;
    }
}