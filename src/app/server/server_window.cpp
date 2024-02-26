#include "server_window.h"
#include "server_manager.h"
#include "chat_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

server_window::server_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    resize(800, 400);

    tabs = new QTabWidget(this);

    list = new QListWidget(this);
    disconnet_all = new QPushButton("Disconnect All", this);
    connect(disconnet_all, &QPushButton::clicked, this, &server_window::disconnet_all_function);

    QVBoxLayout *vbox_1 = new QVBoxLayout();
    vbox_1->addWidget(list);
    vbox_1->addWidget(disconnet_all);

    setup_server();

    QHBoxLayout *HBOX = new QHBoxLayout();
    HBOX->addWidget(tabs, 3);
    HBOX->addLayout(vbox_1);

    central_widget->setLayout(HBOX);
}

void server_window::new_client_connected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    list->addItem(QString("New Client Connected: %1").arg(id));

    chat_window *chat_widget = new chat_window(client);
    tabs->addTab(chat_widget, QString("Client %1").arg(id));
}

void server_window::client_disconnected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    list->addItem(QString("Client disconnected: %1").arg(id));
}

void server_window::setup_server()
{
    _server = new server_manager();
    connect(_server, &server_manager::new_client_connected, this, &server_window::new_client_connected);
    connect(_server, &server_manager::client_disconnected, this, &server_window::client_disconnected);
}

void server_window::disconnet_all_function()
{
    _server->disconnect_all_clients();
}