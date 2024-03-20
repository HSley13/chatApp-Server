#include "client_manager.h"
#include <QFileDialog>
#include <QFile>

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
    QDir *dir = new QDir();
    dir->mkdir("Server");

    QString path = QString("%1/%2/%3_%4").arg(dir->canonicalPath(), "Server", QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

    QFile *file = new QFile(path);

    if (file->open(QIODevice::WriteOnly))
    {
        file->write(_protocol->file_data());
        file->close();

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
        emit text_message_received(_protocol->message());

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

    default:
        break;
    }
}