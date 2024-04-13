#include "chat_protocol.h"
#include <QTime>
#include <QIODevice>
#include <QDataStream>
#include <QFileInfo>
#include <QFile>
#include <QStringList>

chat_protocol::chat_protocol(QWidget *parent)
    : QMainWindow(parent)
{
}

QByteArray chat_protocol::get_data(message_type type, QString data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << type << data;

    return byte;
}

QByteArray chat_protocol::set_text_message(QString sender, QString receiver, QString message)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << text << sender << receiver << message;

    return byte;
}

QByteArray chat_protocol::set_is_typing_message(QString sender, QString receiver)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << is_typing << sender << receiver;

    return byte;
}

QByteArray chat_protocol::set_name_message(QString name)
{
    return get_data(set_name, name);
}

QByteArray chat_protocol::set_init_sending_file_message(QString filename)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    QFileInfo info(filename);

    out << init_sending_file << info.fileName() << info.size();

    return byte;
}

QByteArray chat_protocol::set_accept_file_message()
{
    return get_data(accept_sending_file, "");
}

QByteArray chat_protocol::set_reject_file_message()
{
    return get_data(reject_sending_file, "");
}

QByteArray chat_protocol::set_file_message(QString filename)
{
    QByteArray byte;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream out(&byte, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_0);

        QFileInfo info(filename);

        out << send_file << info.fileName() << info.size() << file.readAll();

        file.close();
    }

    return byte;
}

QByteArray chat_protocol::set_new_client_message(QString client_name)
{
    return get_data(new_client, client_name);
}

QByteArray chat_protocol::set_clients_list_message(QString client_name, QMap<QString, QString> other_clients, int port)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << clients_list << client_name << other_clients << port;

    return byte;
}

QByteArray chat_protocol::set_client_name_message(QString old_name, QString client_name)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << client_new_name << old_name << client_name;

    return byte;
}

QByteArray chat_protocol::set_client_disconnected_message(QString client_name)
{
    return get_data(client_disconnected, client_name);
}

void chat_protocol::load_data(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);

    in >> _type;

    switch (_type)
    {
    case text:
        in >> _sender >> _receiver >> _message;

        break;

    case set_name:
        in >> _name;

        break;

    case is_typing:
        in >> _sender >> _receiver;

    case init_sending_file:
        in >> _file_name >> _file_size;

        break;

    case send_file:
        in >> _file_name >> _file_size >> _file_data;

        break;

    default:
        break;
    }
}

chat_protocol::message_type chat_protocol::type() const
{
    return _type;
}

const QString &chat_protocol::message() const
{
    return _message;
}

const QString &chat_protocol::name() const
{
    return _name;
}

const QString &chat_protocol::file_name() const
{
    return _file_name;
}

const qint64 &chat_protocol::file_size() const
{
    return _file_size;
}

const QByteArray &chat_protocol::file_data() const
{
    return _file_data;
}

const QString &chat_protocol::client_name() const
{
    return _client_name;
}

const QMap<QString, QString> &chat_protocol::other_clients() const
{
    return _other_clients;
}

const QString &chat_protocol::receiver() const
{
    return _receiver;
}

const QString &chat_protocol::sender() const
{
    return _sender;
}