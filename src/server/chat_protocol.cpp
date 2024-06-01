#include "chat_protocol.h"

chat_protocol::chat_protocol(QWidget *parent)
    : QMainWindow(parent) {}

void chat_protocol::load_data(const QByteArray &data)
{
    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_7);

    in >> _type;

    switch (_type)
    {
    case text:
        in >> _sender >> _receiver >> _message >> _time;

        break;

    case set_name:
        in >> _original_name >> _name;

        break;

    case is_typing:
        in >> _sender_typing >> _receiver_typing;

        break;

    case init_send_file:
        in >> _file_sender >> _client_ID >> _file_receiver >> _file_name >> _file_size;

        break;

    case file_accepted:
        in >> _file_sender >> _file_receiver;

        break;

    case file_rejected:
        in >> _file_sender >> _file_receiver;

        break;

    case file:
        in >> _file_sender >> _file_receiver >> _file_name >> _file_data >> _time;

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
        in >> _conversation_ID >> _sender >> _receiver >> _message >> _time;

        break;

    case audio:
        in >> _audio_sender >> _audio_receiver >> _audio_name >> _audio_data >> _time;

        break;

    case save_data:
        in >> _conversation_ID >> _sender >> _receiver >> _file_name >> _file_data >> _data_type >> _time;

        break;

    case sign_up:
        in >> _client_ID >> _first_name >> _last_name >> _password >> _secret_question >> _secret_answer;

        break;

    case login_request:
        in >> _client_ID >> _password;

        break;

    case delete_message:
        in >> _conversation_ID >> _sender >> _receiver >> _time;

        break;

    default:
        break;
    }
}

QByteArray chat_protocol::get_data(message_type type, const QString &data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << type << data;

    return byte;
}

QByteArray chat_protocol::set_text_message(const QString &sender, const QString &receiver, const QString &message, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << text << sender << receiver << message << time;

    return byte;
}

QByteArray chat_protocol::set_is_typing_message(const QString &sender, const QString &receiver)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << is_typing << sender << receiver;

    return byte;
}

QByteArray chat_protocol::set_name_message(const QString &name)
{
    return get_data(set_name, name);
}

QByteArray chat_protocol::set_init_send_file_message(const QString &sender, const QString &sender_ID, const QString &file_name, const qint64 &file_size)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << init_send_file << sender << sender_ID << file_name << file_size;

    return byte;
}

QByteArray chat_protocol::set_file_accepted_message(const QString &sender)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << file_accepted << sender;

    return byte;
}

QByteArray chat_protocol::set_file_rejected_message(const QString &sender)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << file_rejected << sender;

    return byte;
}

QByteArray chat_protocol::set_file_message(const QString &sender, const QString &file_name, const QByteArray &file_data, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << file << sender << file_name << file_data << time;

    return byte;
}

QByteArray chat_protocol::set_client_name_message(const QString &old_name, const QString &client_name)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << client_new_name << old_name << client_name;

    return byte;
}

QByteArray chat_protocol::set_client_disconnected_message(const QString &client_name)
{
    return get_data(client_disconnected, client_name);
}

QByteArray chat_protocol::set_client_connected_message(const QString &client_name)
{
    return get_data(client_connected, client_name);
}

QByteArray chat_protocol::set_added_you_message(const int &conversation_ID, const QString &name, const QString &ID, const QString &receiver)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << added_you << conversation_ID << name << ID << receiver;

    return byte;
}

QByteArray chat_protocol::set_lookup_friend_message(const int &conversation_ID, const QString &ID, bool true_or_false)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << lookup_friend << conversation_ID << ID << true_or_false;

    return byte;
}

QByteArray chat_protocol::set_audio_message(const QString &sender, const QString &audio_name, const QByteArray &audio_data, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << audio << sender << audio_name << audio_data << time;

    return byte;
}

QByteArray chat_protocol::set_login_message(const QString &hashed_password, bool true_or_false, const QString &full_name, const QHash<int, QHash<QString, int>> &friend_list, const QList<QString> &online_friends, const QHash<int, QVector<QString>> &messages, const QHash<int, QHash<QString, QByteArray>> &binary_data)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << login_request << hashed_password << true_or_false << full_name << friend_list << online_friends << messages << binary_data;

    return byte;
}

QByteArray chat_protocol::set_delete_message(const int &conversation_ID, const QString &sender, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << delete_message << sender << time;

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

const QString &chat_protocol::original_name() const
{
    return _original_name;
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

const QString &chat_protocol::file_receiver() const
{
    return _file_receiver;
}

const QString &chat_protocol::file_sender() const
{
    return _file_sender;
}

const QString &chat_protocol::receiver_typing() const
{
    return _receiver_typing;
}

const QString &chat_protocol::sender_typing() const
{
    return _sender_typing;
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

const QString &chat_protocol::time() const
{
    return _time;
}