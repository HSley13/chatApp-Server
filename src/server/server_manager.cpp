#include "server_manager.h"

QHash<QString, QTcpSocket *> server_manager::_clients = QHash<QString, QTcpSocket *>();
sql::Connection *server_manager::_db_connection = nullptr;

server_manager::server_manager(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent)
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &server_manager::on_new_connection);

    _server->listen(_ip, _port);

    _socket = new QTcpSocket(this);

    if (!_db_connection)
        _db_connection = db_connection;
}

server_manager::server_manager(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    _protocol = new chat_protocol(this);

    connect(_socket, &QTcpSocket::readyRead, this, &server_manager::on_ready_read);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void server_manager::on_new_connection()
{
    QTcpSocket *client = _server->nextPendingConnection();

    int id = _clients.count() + 1;
    client->setProperty("id", id);

    QString client_name = QString("client %1").arg(id);

    client->setProperty("client_name", client_name);
    _clients.insert(client_name, client);

    connect(client, &QTcpSocket::disconnected, this, &server_manager::on_client_disconnected);
    emit new_client_connected(client);
}

void server_manager::on_client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    QString client_name = client->property("client_name").toString();

    QByteArray message = _protocol->set_client_disconnected_message(client_name);

    if (!_clients.isEmpty())
    {
        for (QTcpSocket *cl : _clients)
            cl->write(message);
    }
    else
        qDebug() << "server_manager--> client_disconnected() --> _clients is empty, can't send message to other clients";

    emit new_client_disconnected(client);
}

void server_manager::on_ready_read()
{
    QByteArray data = _socket->readAll();

    _protocol->load_data(data);

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

    case chat_protocol::log_in:
        login(_protocol->clients_ID());

        break;

    case chat_protocol::lookup_friend:
        lookup_friend(_protocol->clients_ID());

        break;

    case chat_protocol::create_conversation:
        create_conversation(_protocol->participant1(), _protocol->participant1_ID(), _protocol->participant2(), _protocol->participant2_ID(), _protocol->conversation_ID());

        break;

    case chat_protocol::save_message:
        save_conversation_message(_protocol->sender(), _protocol->receiver(), _protocol->message(), _protocol->conversation_ID());

        break;

    case chat_protocol::audio:
        audio_received(_protocol->audio_sender(), _protocol->audio_receiver(), _protocol->audio_name(), _protocol->audio_data());

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
        QTcpSocket *client = _clients.value(receiver);
        if (client)
            client->write(_protocol->set_text_message(sender, "", message));
        else
            qDebug() << "server_manager -->  on_text_for_other_clients() --> receiver not FOUND" << receiver;
    }
}

void server_manager::audio_received(QString sender, QString receiver, QString audio_name, QByteArray audio_data)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_audio_message(sender, audio_name, audio_data));
    else
        qDebug() << "server_manager -->  on_text_for_other_clients() --> receiver not FOUND" << receiver;
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_manager::disconnect_all_clients()
{
    if (!_clients.isEmpty())
    {
        for (QTcpSocket *client : _clients)
            client->disconnectFromHost();
    }
    else
        qDebug() << "server_manager--> client_disconnected() --> _clients is empty, can't disconnect any clients";
}

void server_manager::disconnect_from_host()
{
    _socket->disconnectFromHost();
}

void server_manager::send_text(QString text)
{
    _socket->write(_protocol->set_text_message("Server", name(), text));
}

void server_manager::send_is_typing(QString sender)
{
    sender = "Server";
    _socket->write(_protocol->set_is_typing_message(sender, ""));
}

void server_manager::send_init_sending_file(QString filename)
{
    _file_name = filename;

    _socket->write(_protocol->set_init_sending_file_message(filename));
}

void server_manager::send_accept_file()
{
    _socket->write(_protocol->set_accept_file_message());
}

void server_manager::send_reject_file()
{
    _socket->write(_protocol->set_reject_file_message());
}

void server_manager::send_file()
{
    emit file_accepted();

    _socket->write(_protocol->set_file_message(_file_name));
}

void server_manager::send_accept_file_client(QString receiver, int port)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_accept_file_message_client(port));
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
    QByteArray message = _protocol->set_client_name_message(old_name, new_name);

    if (!_clients.isEmpty())
    {
        for (QTcpSocket *cl : _clients)
        {
            QString client_name = cl->property("client_name").toString();

            if (client_name.compare(new_name))
                cl->write(message);
        }
    }
    else
        qDebug() << "server_manager--> notify_other_clients()--> _clients is empty, can't send message to other clients";
}

void server_manager::file_for_other_clients(QString sender, QString ID, QString receiver, QString file_name, qint64 file_size)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_init_sending_file_message_client(sender, ID, file_name, file_size));
    else
        qDebug() << "server_manager -->  file_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::reject_receiving_file_clients(QString sender, QString receiver)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_reject_file_message_client(sender, receiver));
    else
        qDebug() << "server_manager --> on_reject_receiving_file_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::is_typing_for_other_clients(QString sender, QString receiver)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_is_typing_message(sender, ""));
    else
        qDebug() << "server_manager --> is_typing_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::login(QString ID)
{
    QString old_name = _socket->property("client_name").toString();
    _clients.remove(_clients.key(_socket));

    _clients.insert(ID, _socket);

    QString name_and_port = QString::fromStdString(Account::retrieve_name_and_port(_db_connection, ID.toInt()));

    QString name = name_and_port.split("/").first();
    _socket->setProperty("client_name", name);

    emit client_name_changed(ID, old_name, name);

    QString port = name_and_port.split("/").last();

    QHash<int, QHash<QString, int>> friend_list = Account::retrieve_friend_list(_db_connection, ID.toInt());

    _socket->write(_protocol->set_login_message(name, port.toInt(), friend_list));
}

void server_manager::lookup_friend(QString ID)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(1024, 49151);

    int conversation_ID = distribution(generator);

    QString name_and_port = QString::fromStdString(Account::retrieve_name_and_port(_db_connection, ID.toInt()));

    _socket->write(_protocol->set_lookup_friend_message(name_and_port.split("/").first(), conversation_ID));

    QString ID_2 = _clients.key(_socket);

    name_and_port = QString::fromStdString(Account::retrieve_name_and_port(_db_connection, ID_2.toInt()));

    QTcpSocket *client = _clients.value(ID);
    if (client)
        client->write(_protocol->set_added_you_message(name_and_port.split("/").first(), ID_2, "", conversation_ID));
}

void server_manager::create_conversation(QString participant1, int participant1_ID, QString participant2, int participant2_ID, int conversation_ID)
{
    Account::create_conversation(_db_connection, participant1.toStdString(), participant1_ID, participant2.toStdString(), participant2_ID, conversation_ID);
}

void server_manager::save_conversation_message(QString sender, QString receiver, QString content, int conversation_ID)
{
    Account::save_message(_db_connection, sender.toInt(), receiver.toInt(), content.toStdString(), conversation_ID);
}