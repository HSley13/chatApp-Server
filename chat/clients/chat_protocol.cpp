#include "chat_protocol.h"
#include <QTime>
#include <QIODevice>
#include <QDataStream>

chat_protocol::chat_protocol(QWidget *parent)
    : QMainWindow(parent)
{
}

QByteArray chat_protocol::text_message(QString message)
{
    return get_data(text, message);
}

QByteArray chat_protocol::is_typing_message()
{
    return get_data(is_typing, "");
}

QByteArray chat_protocol::set_name_message(QString name)
{
    return get_data(set_name, name);
}

void chat_protocol::load_data(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);

    if (in.status() != QDataStream::Ok)
    {
        qDebug() << "Error reading data stream";

        return;
    }

    in >> _type;

    switch (_type)
    {
    case text:
        in >> _message;

        break;

    case set_name:
        in >> _name;

        break;

    case is_typing:
        in >> _is_typing;

        break;

    default:
        qDebug() << "Unknown message type";
        break;
    }
}

QByteArray chat_protocol::get_data(message_type type, QString data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << type << data;

    return byte;
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