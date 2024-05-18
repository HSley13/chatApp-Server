#include "chat_protocol.h"

chat_protocol::chat_protocol(QWidget *parent)
    : QMainWindow(parent) {}

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

QByteArray chat_protocol::set_init_sending_file_message(QString file_name)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    QFileInfo info(file_name);

    out << init_sending_file << info.fileName() << info.size();

    return byte;
}

QByteArray chat_protocol::set_init_sending_file_message_client(QString sender, QString ID, QString file_name, qint64 file_size)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << init_sending_file_client << sender << ID << file_name << file_size;

    return byte;
}

QByteArray chat_protocol::set_accept_file_message()
{
    return get_data(accept_sending_file, "");
}

QByteArray chat_protocol::set_accept_file_message_client(int port)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << accept_sending_file_client << port;

    return byte;
}

QByteArray chat_protocol::set_reject_file_message()
{
    return get_data(reject_sending_file, "");
}

QByteArray chat_protocol::set_reject_file_message_client(QString sender, QString receiver)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << reject_sending_file_client << sender << receiver;

    return byte;
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

QByteArray chat_protocol::set_file_message_client(int port)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << send_file_client << port;

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

QByteArray chat_protocol::set_client_connected_message(QString client_name)
{
    return get_data(client_connected, client_name);
}

QByteArray chat_protocol::set_added_you_message(int conversation_ID, QString name, QString ID, QString receiver)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << added_you << conversation_ID << name << ID << receiver;

    return byte;
}

QByteArray chat_protocol::set_lookup_friend_message(int conversation_ID, QString ID)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << lookup_friend << conversation_ID << ID;

    return byte;
}

QByteArray chat_protocol::set_audio_message(QString sender, QString audio_name, QByteArray audio_data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << audio << sender << audio_name << audio_data;

    return byte;
}

QByteArray chat_protocol::set_login_message(QString hashed_password, bool true_or_false, QString full_name, int port, QHash<int, QHash<QString, int>> friend_list, QList<QString> online_friends, QHash<int, QVector<QString>> messages, QHash<int, QHash<QString, QByteArray>> binary_data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << login_request << hashed_password << true_or_false << full_name << port << friend_list << online_friends << messages << binary_data;

    return byte;
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
        in >> _original_name >> _name;

        break;

    case is_typing:
        in >> _sender_typing >> _receiver_typing;

    case init_sending_file:
        in >> _file_name >> _file_size;

        break;

    case send_file:
        in >> _file_name >> _file_size >> _file_data;

        break;

    case init_sending_file_client:
        in >> _sender >> _client_ID >> _receiver >> _file_name_client >> _file_size_client;

        break;

    case accept_sending_file_client:
        in >> _receiver >> _port;

        break;

    case reject_sending_file_client:
        in >> _sender >> _receiver;

        break;

    case added_you:
        in >> _client_name >> _client_ID >> _receiver;

        break;

    case lookup_friend:
        in >> _client_ID;

        break;

    case create_conversation:
        in >> _conversation_ID >> _participant1 >> _participant1_ID >> _participant2 >> _participant2_ID;

        break;

    case save_message:
        in >> _conversation_ID >> _sender >> _receiver >> _message;

        break;

    case audio:
        in >> _audio_sender >> _audio_receiver >> _audio_name >> _audio_data;

        break;

    case save_data:
        in >> _conversation_ID >> _sender >> _receiver >> _file_name_client >> _file_data >> _data_type;

        break;

    case sign_in:
        in >> _client_ID >> _first_name >> _last_name >> _password >> _secret_question >> _secret_answer;

        break;

    case login_request:
        in >> _client_ID << _password;

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

const QString &chat_protocol::original_name() const
{
    return _original_name;
}

const QString &chat_protocol::file_name() const
{
    return _file_name;
}

const QString &chat_protocol::file_name_client() const
{
    return _file_name_client;
}

const qint64 &chat_protocol::file_size() const
{
    return _file_size;
}

const qint64 &chat_protocol::file_size_client() const
{
    return _file_size_client;
}

const QByteArray &chat_protocol::file_data() const
{
    return _file_data;
}

const QString &chat_protocol::client_name() const
{
    return _client_name;
}

const QHash<QString, QString> &chat_protocol::other_clients() const
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
const QString &chat_protocol::receiver_typing() const
{
    return _receiver_typing;
}

const QString &chat_protocol::sender_typing() const
{
    return _sender_typing;
}

const int &chat_protocol::port() const
{
    return _port;
}

const QString &chat_protocol::clients_ID() const
{
    return _client_ID;
}

const QString &chat_protocol::participant1() const
{
    return _participant1;
}
const int &chat_protocol::participant1_ID() const
{
    return _participant1_ID;
}
const QString &chat_protocol::participant2() const
{
    return _participant2;
}
const int &chat_protocol::participant2_ID() const
{
    return _participant2_ID;
}

const int &chat_protocol::conversation_ID() const
{
    return _conversation_ID;
}

const QString &chat_protocol::audio_name() const
{
    return _audio_name;
}

const QByteArray &chat_protocol::audio_data() const
{
    return _audio_data;
}

const QString &chat_protocol::audio_sender() const
{
    return _audio_sender;
}

const QString &chat_protocol::audio_receiver() const
{
    return _audio_receiver;
}

const QString &chat_protocol::data_type() const
{
    return _data_type;
}

const QString &chat_protocol::last_name() const
{
    return _last_name;
}

const QString &chat_protocol::first_name() const
{
    return _first_name;
}

const QString &chat_protocol::password() const
{
    return _password;
}

const QString &chat_protocol::secret_question() const
{
    return _secret_question;
}

const QString &chat_protocol::secret_answer() const
{
    return _secret_answer;
}