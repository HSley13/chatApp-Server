#include "server_main_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

server_main_window::server_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(800, 400);

    tabs = new QTabWidget(this);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    list = new QListWidget(this);
    disconnect_all = new QPushButton("Disconnect ALL CLIENTS", this);
    connect(disconnect_all, &QPushButton::clicked, this, &server_main_window::disconnect_all_clients);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(list);
    vbox->addWidget(disconnect_all);

    _server = new server_manager();
    connect(_server, &server_manager::new_client_connected, this, &server_main_window::new_client_connected);
    connect(_server, &server_manager::new_client_disconnected, this, &server_main_window::new_client_disconnected);

    QHBoxLayout *Hbox = new QHBoxLayout(central_widget);
    Hbox->addWidget(tabs, 3);
    Hbox->addLayout(vbox);
}

void server_main_window::new_client_connected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    server_chat_window *wid = new server_chat_window(client);
    tabs->addTab(wid, QString("Client %1").arg(id));

    list->addItem(QString("Client %1 Connected").arg(id));

    connect(wid, &server_chat_window::client_name_changed, this, &server_main_window::set_client_name);
    connect(wid, &server_chat_window::is_typing, this, &server_main_window::is_typing_received);
}

void server_main_window::new_client_disconnected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    list->addItem(QString("Client %1 disconnected").arg(id));
}

void server_main_window::set_client_name(QString name)
{
    QWidget *wid = qobject_cast<QWidget *>(sender());
    int index = tabs->indexOf(wid);

    tabs->setTabText(index, name);
}

void server_main_window::disconnect_all_clients()
{
    _server->disconnect_all_clients();
}

void server_main_window::is_typing_received(QString name)
{
    status_bar->showMessage(QString("%1 is typing...").arg(name), 1000);
}