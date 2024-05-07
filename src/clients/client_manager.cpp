#include "client_manager.h"

QTcpSocket *client_manager::_socket = nullptr;
chat_protocol *client_manager::_protocol = nullptr;

QTcpServer *client_manager::_file_server = nullptr;

QString client_manager::_my_ID;
QString client_manager::_full_name;

client_manager::client_manager(QWidget *parent)
    : QMainWindow(parent)
{
    if (!_socket && !_protocol)
    {
        _socket = new QTcpSocket(this);
        _socket->connectToHost(_ip, _port);

        connect(_socket, &QTcpSocket::disconnected, this, &client_manager::on_disconnected);
        connect(_socket, &QTcpSocket::readyRead, this, &client_manager::on_ready_read);

        _protocol = new chat_protocol(this);
    }
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void client_manager::on_ready_read()
{
    QByteArray data = _socket->readAll();
    _protocol->load_data(data);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        emit text_message_received(_protocol->sender(), _protocol->message());

        break;

    case chat_protocol::is_typing:
        emit is_typing_received(_protocol->sender());

        break;

    case chat_protocol::init_sending_file:
        emit init_receiving_file(_protocol->file_name(), _protocol->file_size());

        break;

    case chat_protocol::init_sending_file_client:
        emit init_receiving_file_client(_protocol->sender(), _protocol->clients_ID(), _protocol->file_name_client(), _protocol->file_size_client());

        break;

    case chat_protocol::accept_sending_file:
        send_file();

        break;

    case chat_protocol::accept_sending_file_client:
        send_file_client(_protocol->port_transfer());

        break;

    case chat_protocol::reject_sending_file:
        emit reject_receiving_file();

        break;

    case chat_protocol::reject_sending_file_client:
        emit reject_receiving_file_client(_protocol->sender());

        break;

    case chat_protocol::send_file:
        save_file();

        break;

    case chat_protocol::send_file_client:
        save_file_client(_protocol->sender_file());

        break;

    case chat_protocol::client_new_name:
        emit client_name_changed(_protocol->old_name(), _protocol->client_name());

        break;

    case chat_protocol::client_disconnected:
        emit client_disconnected(_protocol->client_name());

        break;

    case chat_protocol::added_you:
        emit client_added_you(_protocol->client_name(), _protocol->clients_ID(), _protocol->conversation_ID());

        break;

    case chat_protocol::log_in:
    {
        emit friend_list(_protocol->friend_list());

        _full_name = _protocol->full_name();
    }

    break;

    case chat_protocol::lookup_friend:
        emit lookup_friend_result(_protocol->client_name(), _protocol->conversation_ID());

        break;

    default:
        break;
    }
}

void client_manager::on_disconnected()
{
    emit socket_disconnected();
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void client_manager::send_text(QString sender, QString receiver, QString text)
{
    _socket->write(_protocol->set_text_message(sender, receiver, text));
}

void client_manager::send_name(QString name)
{
    _socket->write(_protocol->set_name_message(_protocol->my_name(), name));
}

void client_manager::send_is_typing(QString sender, QString receiver)
{
    _socket->write(_protocol->set_is_typing_message(sender, receiver));
}

void client_manager::send_init_sending_file(QString file_name)
{
    _file_name = file_name;
    _socket->write(_protocol->set_init_sending_file_message(file_name));
}

void client_manager::send_init_sending_file_client(QString sender, QString receiver, QString file_name)
{
    _file_name_client = file_name;
    _socket->write(_protocol->set_init_sending_file_message_client(sender, _my_ID, receiver, file_name));
}

void client_manager::send_accept_file()
{
    _socket->write(_protocol->set_accept_file_message());
}

void client_manager::send_accept_file_client(QString receiver)
{
    _socket->write(_protocol->set_accept_file_message_client(receiver, _protocol->port()));

    if (!_file_server)
    {
        _file_server = new QTcpServer(this);

        _file_server->listen(QHostAddress::LocalHost, _protocol->port());
        connect(_file_server, &QTcpServer::newConnection, this, &client_manager::on_new_connection);
    }
}

void client_manager::on_new_connection()
{
    _file_socket = _file_server->nextPendingConnection();
    connect(_file_socket, &QTcpSocket::readyRead, this, &client_manager::file_connect);
}

void client_manager::file_connect()
{
    QByteArray data;

    data = _file_socket->readAll();
    _protocol->load_data(data);

    save_file_client(_protocol->sender());
}

void client_manager::send_reject_file()
{
    _socket->write(_protocol->set_reject_file_message());
}

void client_manager::send_reject_file_client(QString sender, QString receiver)
{
    _socket->write(_protocol->set_reject_file_message_client(sender, receiver));
}

void client_manager::send_file()
{
    emit file_accepted();

    _socket->write(_protocol->set_file_message(_file_name));
}

void client_manager::send_file_client(int port_transfer)
{
    emit file_accepted_client();

    QTcpSocket *temp = new QTcpSocket(this);
    temp->connectToHost(QHostAddress::LocalHost, port_transfer);

    temp->write(_protocol->set_file_message_client(_file_name_client, _protocol->my_name()));
}

void client_manager::log_in(QString ID)
{
    _my_ID = ID;
    _socket->write(_protocol->set_login_message(ID));
}

void client_manager::save_file()
{
    QDir dir;
    dir.mkdir("Server");

    QString path = QString("%1/%2/%3_%4").arg(dir.canonicalPath(), "Server", QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

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

void client_manager::save_file_client(QString sender)
{
    QDir dir;
    dir.mkdir(sender);

    QString path = QString("%1/%2/%3_%4").arg(dir.canonicalPath(), sender, QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name_client());

    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(_protocol->file_data_client());
        file.close();

        emit file_client_saved(path);
    }
    else
        qDebug() << "client_manager ---> save_file_client() ---> Couldn't open the file to write to it";
}

void client_manager::send_lookup_friend(QString ID)
{
    _socket->write(_protocol->set_lookup_friend_message(ID));
}

void client_manager::send_create_conversation_message(QString participant1, int participant1_ID, QString participant2, int participant2_ID, int conversation_ID)
{
    _socket->write(_protocol->set_create_conversation_message(participant1, participant1_ID, participant2, participant2_ID, conversation_ID));
}

void client_manager::send_save_conversation_message(QString sender, QString receiver, QString content)
{
    _socket->write(_protocol->set_save_message_message(sender, receiver, content));
}
