#include "server_manager.h"
#include <QDir>
#include <QDateTime>
#include <QStringList>
#include <QMessageBox>

port_pool::port_pool(int start, int end)
{
    for (int i = start; i <= end; i++)
        ports.push_back(i);
}

int port_pool::allocate_port()
{
    std::lock_guard<std::mutex> guard(mtx);
    if (!ports.empty())
    {
        int port = ports.back();
        ports.pop_back();

        return port;
    }

    return 0;
}

void port_pool::deallocate_port(int port)
{
    std::lock_guard<std::mutex> guard(mtx);
    ports.push_back(port);
}

void port_pool::deallocate_all()
{
    std::lock_guard<std::mutex> guard(mtx);
    ports.clear();
}

port_pool *server_manager::_pool = nullptr;

QMap<QString, QString> server_manager::_names = QMap<QString, QString>();

server_manager::server_manager(QHostAddress ip, int port, QWidget *parent)
    : QMainWindow(parent),
      _ip(ip), _port(port)
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &server_manager::new_connection);

    _server->listen(_ip, _port);

    _socket = new QTcpSocket(this);

    _pool = new port_pool(12347, 99999);
}

server_manager::server_manager(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    _protocol = new chat_protocol(this);

    connect(_socket, &QTcpSocket::readyRead, this, &server_manager::on_ready_read);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void server_manager::new_connection()
{
    QTcpSocket *client = _server->nextPendingConnection();

    int id = _clients.count() + 1;
    client->setProperty("id", id);

    QString client_name = QString("client %1").arg(id);

    client->setProperty("client_name", client_name);
    _clients.insert(client_name, client);

    _names.insert(client_name, client_name);

    connect(client, &QTcpSocket::disconnected, this, &server_manager::on_client_disconnected);
    emit new_client_connected(client);

    if (id > 1)
    {
        QMap<QString, QString> checked_names;

        for (QMap<QString, QTcpSocket *>::iterator it = _clients.begin(); it != _clients.end(); it++)
        {
            if (_names.contains(it.key()))
                checked_names.insert(it.key(), _names.value(it.key()));
        }

        int port = _pool->allocate_port();
        if (port)
        {
            client->setProperty("port", port);

            QByteArray message = _protocol->set_clients_list_message(client_name, checked_names, port);
            client->write(message);

            qDebug() << "Port: " << port << " assigned to: " << client_name;
        }
        else
            qDebug() << "server_manager--> new_connection()--> _pool vector variable empty";

        QByteArray new_client_message = _protocol->set_new_client_message(client_name);
        for (QTcpSocket *cl : _clients)
            cl->write(new_client_message);
    }
}

void server_manager::on_ready_read()
{
    QByteArray data = _socket->readAll();

    _protocol->load_data(data);

    switch (_protocol->type())
    {
    case chat_protocol::text:
        emit text_message_received(_protocol->sender(), _protocol->receiver(), _protocol->message());

        break;

    case chat_protocol::set_name:
    {
        QString old_name = _socket->property("client_name").toString();
        _socket->setProperty("client_name", _protocol->name());

        emit client_name_changed(old_name, _protocol->name());

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
        file_for_other_clients(_protocol->sender(), _protocol->receiver(), _protocol->file_name());

        break;

    case chat_protocol::accept_sending_file_client:
        send_accept_file_client(_protocol->receiver(), _protocol->port());

        break;

    case chat_protocol::reject_sending_file_client:
        reject_receiving_file_clients(_protocol->sender(), _protocol->receiver());

        break;

    default:
        break;
    }
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_manager::on_client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    QString client_name = client->property("client_name").toString();

    int port = client->property("port").toInt();
    _pool->deallocate_port(port);

    QByteArray message = _protocol->set_client_disconnected_message(client_name);

    if (!_clients.isEmpty())
    {
        for (QTcpSocket *cl : _clients)
            cl->write(message);
    }
    else
        qDebug() << "server_manager--> client_disconnected() --> _clients is empty, can't send message to other clients";

    _clients.remove(client_name);
    _names.remove(client_name);

    emit new_client_disconnected(client);
}

void server_manager::disconnect_all_clients()
{
    if (!_clients.isEmpty())
    {
        for (QTcpSocket *client : _clients)
            client->disconnectFromHost();

        _pool->deallocate_all();
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
    _socket->write(_protocol->set_file_message(_file_name));
}

void server_manager::send_accept_file_client(QString receiver, int port)
{
    QTcpSocket *client = _clients.value(receiver);
    if (client)
        client->write(_protocol->set_accept_file_message_client(port));
    else
        qDebug() << "server_manager--> send_file_client()--> receiver not FOUND: " << receiver;
}

void server_manager::save_file()
{
    QDir *dir = new QDir();
    dir->mkdir(name());

    QString path = QString("%1/%2/%3_%4").arg(dir->canonicalPath(), name(), QDateTime::currentDateTime().toString("yyyMMdd_HHmmss"), _protocol->file_name());

    QFile *file = new QFile(path);

    if (file->open(QIODevice::WriteOnly))
    {
        file->write(_protocol->file_data());
        file->close();

        emit file_saved(path);
    }
}

QString server_manager::name() const
{
    int id = _socket->property("id").toInt();

    QString name = _protocol->name().length() > 0 ? _protocol->name() : QString("Client %1").arg(id);

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

void server_manager::on_text_for_other_clients(QString sender, QString receiver, QString message)
{
    QTcpSocket *client = _clients.value(receiver);

    if (client)
        client->write(_protocol->set_text_message(sender, "", message));

    else
        qDebug() << "server_manager -->  on_text_for_other_clients() --> receiver not FOUND" << receiver;
}

void server_manager::file_for_other_clients(QString sender, QString receiver, QString file_name)
{
    QTcpSocket *client = _clients.value(receiver);

    if (client)
        client->write(_protocol->set_init_sending_file_message_client(sender, file_name));

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
