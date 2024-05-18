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

    QString client_name = client->property("client_name").toString();

    QByteArray message = _protocol->set_client_disconnected_message(client_name);

    if (!_clients.isEmpty())
    {
        for (QWebSocket *cl : _clients)
            cl->sendBinaryMessage(message);
    }
    else
        qDebug() << "server_manager--> client_disconnected() --> _clients is empty, can't send message to other clients";

    emit new_client_disconnected(client);
}

void server_manager::on_binary_message_received(const QByteArray &message)
{
    _protocol->load_data(message);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        message_received(_protocol->sender(), _protocol->receiver(), _protocol->message());

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

    case chat_protocol::init_sending_file:
        emit init_receiving_file(_protocol->name(), _protocol->file_name(), _protocol->file_size());

        break;

    case chat_protocol::accept_sending_file:
        send_file();

        break;

    case chat_protocol::reject_sending_file:
        emit reject_receiving_file(_protocol->name());

        break;

    case chat_protocol::send_file:
        save_file();

        break;

    case chat_protocol::init_sending_file_client:
        file_for_other_clients(_protocol->sender(), _protocol->clients_ID(), _protocol->receiver(), _protocol->file_name_client(), _protocol->file_size_client());

        break;

    case chat_protocol::accept_sending_file_client:
        send_accept_file_client(_protocol->receiver(), _protocol->port());

        break;

    case chat_protocol::reject_sending_file_client:
        reject_receiving_file_clients(_protocol->sender(), _protocol->receiver());

        break;

    case chat_protocol::lookup_friend:
        lookup_friend(_protocol->clients_ID());

        break;

    case chat_protocol::create_conversation:
        create_conversation(_protocol->conversation_ID(), _protocol->participant1(), _protocol->participant1_ID(), _protocol->participant2(), _protocol->participant2_ID());

        break;

    case chat_protocol::save_message:
        save_conversation_message(_protocol->conversation_ID(), _protocol->sender(), _protocol->receiver(), _protocol->message());

        break;

    case chat_protocol::audio:
        audio_received(_protocol->audio_sender(), _protocol->audio_receiver(), _protocol->audio_name(), _protocol->audio_data());

        break;

    case chat_protocol::save_data:
        save_data_client(_protocol->conversation_ID(), _protocol->sender(), _protocol->receiver(), _protocol->file_name_client(), _protocol->file_data(), _protocol->data_type());

        break;

    case chat_protocol::sign_in:
        sign_in(_protocol->clients_ID(), _protocol->first_name(), _protocol->last_name(), _protocol->password(), _protocol->secret_question(), _protocol->secret_answer());

        break;

    case chat_protocol::login_request:
        login_request(_protocol->clients_ID(), _protocol->password());

        break;

    default:
        break;
    }
}

void server_manager::message_received(QString sender, QString receiver, QString message)
{
    if (!receiver.compare("Server"))
        emit text_message_received(message);
    else
    {
        QWebSocket *client = _clients.value(receiver);
        if (client)
            client->sendBinaryMessage(_protocol->set_text_message(sender, "", message));
        else
            qDebug() << "server_manager -->  on_text_for_other_clients() --> receiver not FOUND" << receiver;
    }
}

void server_manager::audio_received(QString sender, QString receiver, QString audio_name, QByteArray audio_data)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_audio_message(sender, audio_name, audio_data));
    else
        qDebug() << "server_manager -->  on_text_for_other_clients() --> receiver not FOUND" << receiver;
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_manager::disconnect_all_clients()
{
    if (!_clients.isEmpty())
    {
        for (QWebSocket *client : _clients)
            client->close();
    }
    else
        qDebug() << "server_manager--> client_disconnected() --> _clients is empty, can't disconnect any clients";
}

void server_manager::disconnect_from_host()
{
    _socket->close();
}

void server_manager::send_text(QString text)
{
    _socket->sendBinaryMessage(_protocol->set_text_message("Server", name(), text));
}

void server_manager::send_is_typing(QString sender)
{
    sender = "Server";
    _socket->sendBinaryMessage(_protocol->set_is_typing_message(sender, ""));
}

void server_manager::send_init_sending_file(QString filename)
{
    _file_name = filename;

    _socket->sendBinaryMessage(_protocol->set_init_sending_file_message(filename));
}

void server_manager::send_accept_file()
{
    _socket->sendBinaryMessage(_protocol->set_accept_file_message());
}

void server_manager::send_reject_file()
{
    _socket->sendBinaryMessage(_protocol->set_reject_file_message());
}

void server_manager::send_file()
{
    emit file_accepted();

    _socket->sendBinaryMessage(_protocol->set_file_message(_file_name));
}

void server_manager::send_accept_file_client(QString receiver, int port)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_accept_file_message_client(port));
    else
        qDebug() << "server_manager--> send_accept_file_client()--> receiver not FOUND: " << receiver;
}

void server_manager::save_file()
{
    QDir dir;
    dir.mkdir(name());

    QString path = QString("%1/%2/%3_%4").arg(dir.canonicalPath(), name(), QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(_protocol->file_data());
        file.close();

        emit file_saved(path);
    }
    else
        qDebug() << "client_manager ---> save_file() ---> Couldn't open the file to write to it";
}

QString server_manager::name() const
{
    QString name = _protocol->name().length() > 0 ? _protocol->name() : _socket->property("client_name").toString();

    return name;
}

void server_manager::notify_other_clients(QString old_name, QString new_name)
{
    QByteArray message_1 = _protocol->set_client_name_message(old_name, new_name);

    QByteArray message_2 = _protocol->set_client_connected_message(new_name);

    if (!_clients.isEmpty())
    {
        for (QWebSocket *cl : _clients)
        {
            QString client_name = cl->property("client_name").toString();

            if (client_name.compare(new_name))
            {
                if (!old_name.compare(""))
                    cl->sendBinaryMessage(message_2);
                else
                    cl->sendBinaryMessage(message_1);
            }
        }
    }
    else
        qDebug() << "server_manager--> notify_other_clients()--> _clients is empty, can't send message to other clients";
}

void server_manager::file_for_other_clients(QString sender, QString ID, QString receiver, QString file_name, qint64 file_size)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_init_sending_file_message_client(sender, ID, file_name, file_size));
    else
        qDebug() << "server_manager -->  file_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::reject_receiving_file_clients(QString sender, QString receiver)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_reject_file_message_client(sender, receiver));
    else
        qDebug() << "server_manager --> on_reject_receiving_file_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::is_typing_for_other_clients(QString sender, QString receiver)
{
    QWebSocket *client = _clients.value(receiver);
    if (client)
        client->sendBinaryMessage(_protocol->set_is_typing_message(sender, ""));
    else
        qDebug() << "server_manager --> is_typing_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::lookup_friend(QString ID)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(1024, 49151);

    int conversation_ID = distribution(generator);

    QString name_and_port = Account::retrieve_name_and_port(_db_connection, ID.toInt());

    _socket->sendBinaryMessage(_protocol->set_lookup_friend_message(conversation_ID, name_and_port.split("/").first()));

    QString ID_2 = _clients.key(_socket);

    name_and_port = Account::retrieve_name_and_port(_db_connection, ID_2.toInt());

    QWebSocket *client = _clients.value(ID);
    if (client)
        client->sendBinaryMessage(_protocol->set_added_you_message(conversation_ID, name_and_port.split("/").first(), ID_2, ""));
}

void server_manager::create_conversation(int conversation_ID, QString participant1, int participant1_ID, QString participant2, int participant2_ID)
{
    Account::create_conversation(_db_connection, conversation_ID, participant1.toStdString(), participant1_ID, participant2.toStdString(), participant2_ID);
}

void server_manager::save_conversation_message(int conversation_ID, QString sender, QString receiver, QString content)
{
    Account::save_text_message(_db_connection, conversation_ID, sender.toInt(), receiver.toInt(), content.toStdString());
}

void server_manager::save_data_client(int conversation_ID, QString sender, QString receiver, QString file_name, QByteArray file_data, QString data_type)
{
    Account::save_binary_data(_db_connection, conversation_ID, sender.toInt(), receiver.toInt(), file_name.toStdString(), file_data, file_data.size(), data_type.toStdString());
}

void server_manager::sign_in(QString phone_number, QString first_name, QString last_name, QString password, QString secret_question, QString secret_answer)
{
    Account::create_account(_db_connection, phone_number.toInt(), first_name.toStdString(), last_name.toStdString(), password.toStdString(), secret_question.toStdString(), secret_answer.toStdString());
}

void server_manager::login_request(QString phone_number, QString password)
{
    if (phone_number.isEmpty())
        return;

    QString old_name = _socket->property("client_name").toString();
    _clients.remove(_clients.key(_socket));

    _clients.insert(phone_number, _socket);

    QString name_and_port = Account::retrieve_name_and_port(_db_connection, phone_number.toInt());

    if (!name_and_port.compare(""))
        return;
    // Correct the line above

    QString name = name_and_port.split("/").first();
    _socket->setProperty("client_name", name);

    QString port = name_and_port.split("/").last();

    _names.insert(phone_number, name);

    emit client_name_changed(phone_number, old_name, name);

    std::string hashed_password = Security::retrieve_hashed_password(_db_connection, phone_number.toInt());

    QHash<int, QHash<QString, int>> friend_list;

    QList<QString> online_friends;

    QHash<int, QVector<QString>> messages;

    QHash<int, QHash<QString, QByteArray>> binary_data;

    if (Security::verifying_password(password.toStdString(), hashed_password))
    {
        friend_list = Account::retrieve_friend_list(_db_connection, phone_number.toInt());

        for (QHash<QString, int> &info : friend_list)
        {
            for (int friend_id : info.values())
            {
                if (_clients.contains(QString::number(friend_id)))
                {
                    QString friend_name = _names.value(QString::number(friend_id));
                    online_friends << friend_name;
                }
            }

            messages[friend_list.key(info)] = Account::retrieve_conversation(_db_connection, friend_list.key(info));
            binary_data[friend_list.key(info)] = Account::retrieve_binary_data(_db_connection, friend_list.key(info));
        }

        _socket->sendBinaryMessage(_protocol->set_login_message(QString::fromStdString(hashed_password), true, name, port.toInt(), friend_list, online_friends, messages, binary_data));
        notify_other_clients("", name);
    }
    else
    {
        _socket->sendBinaryMessage(_protocol->set_login_message(QString::fromStdString(hashed_password), false, name, port.toInt(), friend_list, online_friends, messages, binary_data));
        _clients.remove(name);
        _names.remove(name);
        _socket->close();
    }
}
