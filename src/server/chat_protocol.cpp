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
        in >> _client_ID >> _password >> _time_zone;

        break;

    case delete_message:
        in >> _conversation_ID >> _sender >> _receiver >> _time;

        break;

    case delete_group_message:
        in >> _group_ID >> _group_name >> _time;

        break;

    case new_group:
        in >> _adm >> _members >> _group_name;

        break;

    case group_is_typing:
        in >> _group_ID >> _group_name >> _group_sender;

        break;

    case group_text:
        in >> _group_ID >> _group_name >> _group_sender >> _group_message >> _group_time;

        break;

    case group_audio:
        in >> _group_ID >> _group_name >> _group_sender >> _group_audio_name >> _group_audio_data >> _group_time;

        break;

    case group_file:
        in >> _group_ID >> _group_name >> _group_sender >> _group_file_name >> _group_file_data >> _group_time;

        break;

    case new_group_member:
        in >> _group_ID >> _group_name >> _adm >> _client_ID;

        break;

    case remove_group_member:
        in >> _group_ID >> _group_name >> _adm >> _client_ID;

        break;

    case request_data:
        in >> _conversation_ID >> _time >> _data_type;

        break;

    case delete_account:
        in >> _client_ID;

        break;

    case last_message_read:
        in >> _conversation_ID >> _client_ID >> _time;

        break;

    case group_last_message_read:
        in >> _group_ID >> _client_ID >> _time;

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

QByteArray chat_protocol::set_text_message(const QString &sender, const QString &message, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << text << sender << message << time;

    return byte;
}

QByteArray chat_protocol::set_is_typing_message(const QString &sender)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << is_typing << sender;

    return byte;
}

QByteArray chat_protocol::set_name_message(const QString &name)
{
    return get_data(set_name, name);
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

QByteArray chat_protocol::set_added_you_message(const int &conversation_ID, const QString &name, const QString &ID)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << added_you << conversation_ID << name << ID;

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

QByteArray chat_protocol::set_login_message(const QString &hashed_password, bool true_or_false, const QString &name, const QHash<int, QHash<QString, QString>> &friend_list, const QStringList &online_friends, const QHash<int, QStringList> &messages, const QHash<int, QHash<int, QString>> &group_list, const QHash<int, QStringList> &group_messages, const QHash<int, QStringList> &group_members)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << login_request << hashed_password << true_or_false << name << friend_list << online_friends << messages << group_list << group_messages << group_members;

    return byte;
}

QByteArray chat_protocol::set_delete_message(const QString &sender, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << delete_message << sender << time;

    return byte;
}

QByteArray chat_protocol::set_new_group_message(const int &group_ID)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << new_group << group_ID;

    return byte;
}

QByteArray chat_protocol::set_added_to_group_message(const int &group_ID, const QString &adm, const QStringList &group_members, const QString &group_name)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << added_to_group << group_ID << adm << group_members << group_name;

    return byte;
}

QByteArray chat_protocol::set_group_is_typing(const int &group_ID, const QString &group_name, const QString &sender)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << group_is_typing << group_ID << group_name << sender;

    return byte;
}

QByteArray chat_protocol::set_group_text_message(const int &group_ID, const QString &group_name, const QString &sender, const QString &message, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << group_text << group_ID << group_name << sender << message << time;

    return byte;
}

QByteArray chat_protocol::set_group_file_message(const int &group_ID, const QString &group_name, const QString &sender, const QString &file_name, const QByteArray &file_data, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << group_file << group_ID << group_name << sender << file_name << file_data << time;

    return byte;
}

QByteArray chat_protocol::set_group_audio_message(const int &group_ID, const QString &group_name, const QString &sender, const QString &audio_name, const QByteArray &audio_data, const QString &time)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << group_audio << group_ID << group_name << sender << audio_name << audio_data << time;

    return byte;
}

QByteArray chat_protocol::set_removed_from_group(const int &group_ID, const QString &group_name, const QString &adm, const QString &removed_member)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << remove_group_member << group_ID << group_name << adm << removed_member;

    return byte;
}

QByteArray chat_protocol::set_data_requested_found_message(const QByteArray &file_data, const QString &type)
{
    QByteArray byte;

    QDataStream out(&byte, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);

    out << request_data << file_data << type;

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

const QString &chat_protocol::group_file_name() const
{
    return _group_file_name;
}

const qint64 &chat_protocol::group_file_size() const
{
    return _group_file_size;
}

const QByteArray &chat_protocol::group_file_data() const
{
    return _group_file_data;
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

const QString &chat_protocol::group_file_sender() const
{
    return _group_file_sender;
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

const QString &chat_protocol::group_audio_name() const
{
    return _group_audio_name;
}

const QByteArray &chat_protocol::group_audio_data() const
{
    return _group_audio_data;
}

const QString &chat_protocol::group_audio_sender() const
{
    return _group_audio_sender;
}

const QString &chat_protocol::group_data_type() const
{
    return _group_data_type;
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

const int &chat_protocol::group_ID() const
{
    return _group_ID;
}

const QString &chat_protocol::adm() const
{
    return _adm;
}

const QString &chat_protocol::group_sender() const
{
    return _group_sender;
}

const QStringList &chat_protocol::members() const
{
    return _members;
}

const QString &chat_protocol::group_name() const
{
    return _group_name;
}

const QString &chat_protocol::group_message() const
{
    return _group_message;
}

const QString &chat_protocol::group_time() const
{
    return _group_time;
}

const QString &chat_protocol::time_zone() const
{
    return _time_zone;
}