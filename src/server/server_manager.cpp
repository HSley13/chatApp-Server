#include "server_manager.h"

QHash<QString, QWebSocket *> server_manager::_clients = QHash<QString, QWebSocket *>();

QHash<QString, QString> server_manager::_names = QHash<QString, QString>();

sql::Connection *server_manager::_db_connection = nullptr;

server_manager::server_manager(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent)
{
    _server = new QWebSocketServer(QString("ChatApp Server"), QWebSocketServer::NonSecureMode, this);
    connect(_server, &QWebSocketServer::newConnection, this, &server_manager::on_new_connection);

    _server->listen(_ip, _port);

    _socket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);

    if (!_db_connection)
        _db_connection = db_connection;
}

server_manager::server_manager(QWebSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    _protocol = new chat_protocol(this);

    connect(_socket, &QWebSocket::binaryMessageReceived, this, &server_manager::on_binary_message_received);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void server_manager::on_binary_message_received(const QByteArray &message)
{
    _protocol->load_data(message);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        message_received(_protocol->sender(), _protocol->receiver(), _protocol->message(), _protocol->time());

        break;

    case chat_protocol::set_name:
    {
        QString old_name = _socket->property("client_name").toString();
        _socket->setProperty("client_name", _protocol->name());

        emit client_name_changed(_protocol->original_name(), old_name, _protocol->name());
        emit notify_other_clients(old_name, _protocol->name());

        Account::update_alias(_db_connection, _clients.key(_socket).toInt(), _protocol->name().toStdString());

        break;
    }

    case chat_protocol::is_typing:
        emit is_typing_received(_protocol->sender_typing(), _protocol->receiver_typing());

        break;

    case chat_protocol::file:
        file_received(_protocol->file_sender(), _protocol->file_receiver(), _protocol->file_name(), _protocol->file_data(), _protocol->time());

        break;

    case chat_protocol::lookup_friend:
        lookup_friend(_protocol->clients_ID());

        break;

    case chat_protocol::create_conversation:
        create_conversation(_protocol->conversation_ID(), _protocol->participant1(), _protocol->participant1_ID(), _protocol->participant2(), _protocol->participant2_ID());

        break;

    case chat_protocol::save_message:
        save_conversation_message(_protocol->conversation_ID(), _protocol->sender(), _protocol->receiver(), _protocol->message(), _protocol->time());

        break;

    case chat_protocol::audio:
        audio_received(_protocol->audio_sender(), _protocol->audio_receiver(), _protocol->audio_name(), _protocol->audio_data(), _protocol->time());

        break;

    case chat_protocol::save_data:
        save_data(_protocol->conversation_ID(), _protocol->sender(), _protocol->receiver(), _protocol->file_name(), _protocol->file_data(), _protocol->data_type(), _protocol->time());

        break;

    case chat_protocol::sign_up:
        sign_up(_protocol->clients_ID(), _protocol->first_name(), _protocol->last_name(), _protocol->password(), _protocol->secret_question(), _protocol->secret_answer());

        break;

    case chat_protocol::login_request:
        login_request(_protocol->clients_ID(), _protocol->password());

        break;

    case chat_protocol::delete_message:
        delete_message(_protocol->conversation_ID(), _protocol->sender(), _protocol->receiver(), _protocol->time());

        break;

    case chat_protocol::new_group:
        create_new_group(_protocol->adm(), _protocol->members(), _protocol->group_name());

        break;

    case chat_protocol::group_is_typing:
        group_is_typing_received(_protocol->group_ID(), _protocol->group_name(), _protocol->group_sender());

        break;

    case chat_protocol::group_text:
        group_text_received(_protocol->group_ID(), _protocol->group_name(), _protocol->group_sender(), _protocol->group_message(), _protocol->group_time());

        break;

    case chat_protocol::group_audio:
        group_audio_received(_protocol->group_ID(), _protocol->group_name(), _protocol->group_sender(), _protocol->group_audio_name(), _protocol->group_audio_data(), _protocol->group_time());

        break;

    case chat_protocol::group_file:
        group_file_received(_protocol->group_ID(), _protocol->group_name(), _protocol->group_sender(), _protocol->group_file_name(), _protocol->group_file_data(), _protocol->group_time());

        break;

    case chat_protocol::new_group_member:
        new_group_member(_protocol->group_ID(), _protocol->group_name(), _protocol->adm(), _protocol->clients_ID());

        break;

    case chat_protocol::remove_group_member:
        remove_group_member(_protocol->group_ID(), _protocol->group_name(), _protocol->adm(), _protocol->clients_ID());

        break;

    case chat_protocol::request_data:
        data_requested(_protocol->conversation_ID(), _protocol->time(), _protocol->data_type());

        break;

    case chat_protocol::delete_account:
        delete_account(_protocol->clients_ID());

    default:
        break;
    }
}

void server_manager::on_new_connection()
{
    QWebSocket *client = _server->nextPendingConnection();

    int id = _clients.count() + 1;
    client->setProperty("id", id);

    QString client_name = QString("client %1").arg(id);

    client->setProperty("client_name", client_name);
    _clients.insert(client_name, client);

    connect(client, &QWebSocket::disconnected, this, &server_manager::on_client_disconnected);
    emit new_client_connected(client);
}

void server_manager::on_client_disconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());

    _clients.remove(_clients.key(client));

    QString client_name = client->property("client_name").toString();

    QByteArray message = _protocol->set_client_disconnected_message(client_name);

    if (!_clients.isEmpty())
    {
        for (QWebSocket *cl : _clients)
            cl->sendBinaryMessage(message);
    }

    emit new_client_disconnected(client);
}

void server_manager::message_received(const QString &sender, const QString &receiver, const QString &message, const QString &time)
{
    if (!receiver.compare("Server"))
        emit text_message_received(message, time);
    else
    {
        QWebSocket *client = _clients.value(receiver);
        if (client)
            client->sendBinaryMessage(_protocol->set_text_message(sender, message, time));
    }
}

void server_manager::audio_received(const QString &sender, const QString &receiver, const QString &audio_name, const QByteArray &audio_data, const QString &time)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_audio_message(sender, audio_name, audio_data, time));
}

void server_manager::file_received(const QString &sender, const QString &receiver, const QString &file_name, const QByteArray &file_data, const QString &time)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_file_message(sender, file_name, file_data, time));
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_manager::disconnect_all_clients()
{
    if (!_clients.isEmpty())
    {
        for (QWebSocket *client : _clients)
            client->close();
    }
}

void server_manager::disconnect_from_host()
{
    _socket->close();
}

void server_manager::send_text(const QString &text, const QString &time)
{
    _socket->sendBinaryMessage(_protocol->set_text_message("Server", text, time));
}

void server_manager::send_is_typing(const QString &sender)
{
    _socket->sendBinaryMessage(_protocol->set_is_typing_message("Server"));
}

void server_manager::is_typing_for_other_clients(const QString &sender, const QString &receiver)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_is_typing_message(sender));
}

QString server_manager::name() const
{
    QString name = _protocol->name().length() > 0 ? _protocol->name() : _socket->property("client_name").toString();

    return name;
}

void server_manager::notify_other_clients(const QString &old_name, const QString &new_name)
{
    QByteArray message_1 = _protocol->set_client_name_message(old_name, new_name);

    QByteArray message_2 = _protocol->set_client_connected_message(new_name);

    QHash<int, QHash<QString, QString>> friend_list = Account::retrieve_friend_list(_db_connection, _clients.key(_socket).toInt());
    QStringList friend_IDs;
    for (QHash<QString, QString> info : friend_list)
    {
        for (QString ID : info.keys())
            friend_IDs << ID;
    }

    std::function<void(const QByteArray &)> send_messages = [&](const QByteArray &message)
    {
        for (const QString &ID : friend_IDs)
        {
            if (_clients.contains(ID))
                _clients.value(ID)->sendBinaryMessage(message);
        }
    };

    if (!old_name.isEmpty())
        send_messages(message_1);
    else
        send_messages(message_2);

    QHash<int, QHash<int, QString>> group_list = Account::retrieve_group_list(_db_connection, _clients.key(_socket).toInt());
    for (const int &group_ID : group_list.keys())
    {
        QStringList group_members = Account::retrieve_group_members(_db_connection, group_ID);
        for (const QString &ID : group_members)
        {
            if (_clients.contains(ID))
                _clients.value(ID)->sendBinaryMessage(message_1);
        }
    }
}

void server_manager::lookup_friend(const QString &ID)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(1024, 49151);

    int conversation_ID = distribution(generator);

    QString alias = Account::retrieve_alias(_db_connection, ID.toInt());

    bool true_or_false = (_clients.contains(ID)) ? true : false;

    _socket->sendBinaryMessage(_protocol->set_lookup_friend_message(conversation_ID, alias, true_or_false));

    const QString &ID_2 = _clients.key(_socket);

    alias = Account::retrieve_alias(_db_connection, ID_2.toInt());

    QWebSocket *client = _clients.value(ID);
    if (client)
        client->sendBinaryMessage(_protocol->set_added_you_message(conversation_ID, alias, ID_2));
}

void server_manager::create_conversation(const int &conversation_ID, const QString &participant1, const int &participant1_ID, const QString &participant2, const int &participant2_ID)
{
    Account::create_conversation(_db_connection, conversation_ID, participant1.toStdString(), participant1_ID, participant2.toStdString(), participant2_ID);
}

void server_manager::save_conversation_message(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &content, const QString &time)
{
    Account::save_text_message(_db_connection, conversation_ID, sender.toInt(), receiver.toInt(), content.toStdString(), time.toStdString());
}

void server_manager::save_data(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &data_name, const QByteArray &data_data, const QString &data_type, const QString &time)
{
    Account::save_binary_data(_db_connection, conversation_ID, sender.toInt(), receiver.toInt(), data_name.toStdString(), data_data, data_data.size(), data_type.toStdString(), time.toStdString());
}

void server_manager::sign_up(const QString &phone_number, const QString &first_name, const QString &last_name, const QString &password, const QString &secret_question, const QString &secret_answer)
{
    Account::create_account(_db_connection, phone_number.toInt(), first_name.toStdString(), last_name.toStdString(), secret_question.toStdString(), secret_answer.toStdString(), password.toStdString());

    QTimer::singleShot(3000, this, [this]()
                       { _socket->close(); });
}

void server_manager::login_request(const QString &phone_number, const QString &password)
{
    if (phone_number.isEmpty())
        return;

    QString old_name = _socket->property("client_name").toString();
    _clients.remove(_clients.key(_socket));

    _clients.insert(phone_number, _socket);

    QString name = Account::retrieve_alias(_db_connection, phone_number.toInt());

    if (name.isEmpty())
    {
        _socket->sendBinaryMessage(_protocol->set_login_message(QString(), false, QString(), QHash<int, QHash<QString, QString>>(), QStringList(), QHash<int, QStringList>(), QHash<int, QHash<int, QString>>(), QHash<int, QStringList>(), QHash<int, QStringList>()));

        _clients.remove(name);
        _names.remove(name);

        return;
    }

    _socket->setProperty("client_name", name);

    _names.insert(phone_number, name);

    emit client_name_changed(phone_number, old_name, name);

    std::string hashed_password = Security::retrieve_hashed_password(_db_connection, phone_number.toInt());

    QHash<int, QHash<QString, QString>> friend_list;

    QStringList online_friends;

    QHash<int, QStringList> messages;

    QHash<int, QHash<QString, QByteArray>> binary_data;

    QHash<int, QHash<int, QString>> group_list;

    QHash<int, QStringList> group_messages;

    QHash<int, QHash<QString, QByteArray>> group_binary_data;

    QHash<int, QStringList> group_members;

    if (Security::verifying_password(password.toStdString(), hashed_password))
    {
        friend_list = Account::retrieve_friend_list(_db_connection, phone_number.toInt());

        for (QHash<QString, QString> &info : friend_list)
        {
            for (QString friend_ID : info.keys())
            {
                if (_clients.contains(friend_ID))
                    online_friends << info.value(friend_ID);
            }

            messages.insert(friend_list.key(info), Account::retrieve_conversation(_db_connection, friend_list.key(info), _clients.key(_socket).toInt()));
        }

        group_list = Account::retrieve_group_list(_db_connection, phone_number.toInt());

        for (int group_ID : group_list.keys())
        {
            group_messages.insert(group_ID, Account::retrieve_group_conversation(_db_connection, group_ID));
            group_members.insert(group_ID, Account::retrieve_group_members(_db_connection, group_ID));
        }

        _socket->sendBinaryMessage(_protocol->set_login_message(QString::fromStdString(hashed_password), true, name, friend_list, online_friends, messages, group_list, group_messages, group_members));
        notify_other_clients("", name);
    }
    else
    {
        _socket->sendBinaryMessage(_protocol->set_login_message(QString::fromStdString(hashed_password), false, name, QHash<int, QHash<QString, QString>>(), QStringList(), QHash<int, QStringList>(), QHash<int, QHash<int, QString>>(), QHash<int, QStringList>(), QHash<int, QStringList>()));
        _clients.remove(name);
        _names.remove(name);
    }
}

void server_manager::delete_message(const int &conversation_ID, const QString &sender, const QString &receiver, const QString &time)
{
    Account::delete_message(_db_connection, conversation_ID, time.toStdString());

    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_delete_message(conversation_ID, sender, time));
}

void server_manager::create_new_group(const QString &adm, const QStringList &members, const QString &group_name)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(1024, 49151);

    int group_ID = distribution(generator);

    _socket->sendBinaryMessage(_protocol->set_new_group_message(group_ID));

    Account::add_to_group(_db_connection, group_ID, group_name.toStdString(), _clients.key(_socket).toInt(), "admin");

    for (QString ID : members)
    {
        Account::add_to_group(_db_connection, group_ID, group_name.toStdString(), ID.toInt(), "member");

        if (ID.compare(_clients.key(_socket)))
        {
            QWebSocket *client = _clients.value(ID);
            if (client)
                client->sendBinaryMessage(_protocol->set_added_to_group_message(group_ID, adm, members, group_name));
        }
    }
}

void server_manager::group_is_typing_received(const int &group_ID, const QString &group_name, const QString &sender)
{
    QStringList members = Account::retrieve_group_members(_db_connection, group_ID);
    if (!members.isEmpty())
    {
        for (QString ID : members)
        {
            if (ID.compare(_clients.key(_socket)))
            {
                QWebSocket *client = _clients.value(ID);
                if (client)
                    client->sendBinaryMessage(_protocol->set_group_is_typing(group_ID, group_name, sender));
            }
        }
    }
}

void server_manager::group_text_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &message, const QString &time)
{
    QStringList members = Account::retrieve_group_members(_db_connection, group_ID);
    if (!members.isEmpty())
    {
        Account::save_group_text_message(_db_connection, group_ID, sender.toStdString(), message.toStdString(), time.toStdString());

        for (QString ID : members)
        {
            if (ID.compare(_clients.key(_socket)))
            {
                QWebSocket *client = _clients.value(ID);
                if (client)
                    client->sendBinaryMessage(_protocol->set_group_text_message(group_ID, group_name, sender, message, time.split(" ").last()));
            }
        }
    }
}

void server_manager::group_file_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &file_name, const QByteArray &file_data, const QString &time)
{
    QStringList members = Account::retrieve_group_members(_db_connection, group_ID);
    if (!members.isEmpty())
    {
        Account::save_group_binary_data(_db_connection, group_ID, sender.toStdString(), file_name.split("_").last().toStdString(), file_data, file_data.size(), "file", time.toStdString());

        for (QString ID : members)
        {
            if (ID.compare(_clients.key(_socket)))
            {
                QWebSocket *client = _clients.value(ID);
                if (client)
                    client->sendBinaryMessage(_protocol->set_group_file_message(group_ID, group_name, sender, file_name, file_data, time.split(" ").last()));
            }
        }
    }
}

void server_manager::group_audio_received(const int &group_ID, const QString &group_name, const QString &sender, const QString &audio_name, const QByteArray &audio_data, const QString &time)
{
    QStringList members = Account::retrieve_group_members(_db_connection, group_ID);
    if (!members.isEmpty())
    {
        Account::save_group_binary_data(_db_connection, group_ID, sender.toStdString(), audio_name.split("_").last().toStdString(), audio_data, audio_data.size(), "audio", time.toStdString());

        for (QString ID : members)
        {
            if (ID.compare(_clients.key(_socket)))
            {
                QWebSocket *client = _clients.value(ID);
                if (client)
                    client->sendBinaryMessage(_protocol->set_group_audio_message(group_ID, group_name, sender, audio_name, audio_data, time.split(" ").last()));
            }
        }
    }
}

void server_manager::new_group_member(const int &group_ID, const QString &group_name, const QString &adm, const QString &group_member)
{
    Account::add_to_group(_db_connection, group_ID, group_name.toStdString(), group_member.toInt(), "member");

    const QStringList &members = Account::retrieve_group_members(_db_connection, group_ID);

    QWebSocket *client = _clients.value(group_member);
    if (client)
        client->sendBinaryMessage(_protocol->set_added_to_group_message(group_ID, adm, members, group_name));
}

void server_manager::remove_group_member(const int &group_ID, const QString &group_name, const QString &adm, const QString &group_member)
{
    Account::remove_from_group(_db_connection, group_ID, group_member.toInt());

    QWebSocket *client = _clients.value(group_member);
    if (client)
        client->sendBinaryMessage(_protocol->set_removed_from_group(group_ID, group_name, adm));
}

void server_manager::data_requested(const int &conversation_ID, const QString &date_time, const QString &type)
{
    const QHash<QString, QByteArray> &file_data = (!type.compare("normal")) ? Account::retrieve_binary_data(_db_connection, conversation_ID, date_time.toStdString()) : Account::retrieve_group_binary_data(_db_connection, conversation_ID, date_time.toStdString());

    _socket->sendBinaryMessage(_protocol->set_data_requested_found_message(file_data.values().first(), file_data.keys().first()));
}

void server_manager::delete_account(const QString &phone_number)
{
    Account::delete_account(_db_connection, phone_number.toInt());
}

void server_manager::update_last_message_read(const int &conversation_ID, const QString &client_ID, const QString &time)
{
    Account::update_last_message_read(_db_connection, conversation_ID, client_ID.toInt(), time.toStdString());
}