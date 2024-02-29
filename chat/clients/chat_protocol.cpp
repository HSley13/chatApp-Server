#include "chat_protocol.h"
#include <QTime>
#include <QIODevice>

chat_protocol::chat_protocol(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);
}

QByteArray chat_protocol::get_data(message_type type, QString message)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << type << message;

    return byte;
}

QByteArray chat_protocol::text_message(QString message)
{
    return get_data(text, message);
}

QByteArray chat_protocol::is_typing_func()
{
    return get_data(is_typing, "");
}

QByteArray chat_protocol::set_name_func(QString message)
{
    return get_data(set_name, message);
}

void chat_protocol::laod_data(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);

    in >> _type;

    switch (_type)
    {
    case text:
        in >> _message;

        break;

    case set_name:
        in >> _set_name;

        break;

    case is_typing:
        in >> _is_typing;

        break;

    default:
        break;
    }
}

chat_protocol::message_type chat_protocol::G_type() const
{
    return _type;
}

const QString &chat_protocol::G_message() const
{
    return _message;
}
const QString &chat_protocol::G_set_name() const
{
    return _set_name;
}
const QString &chat_protocol::G_is_typing() const
{
    return _is_typing;
}