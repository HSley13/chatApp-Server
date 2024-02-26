#include "client_window.h"
#include "client_manager.h"
#include "client_chat.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>

client_window::client_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    menu = new QMenu(this);
    menu = menu_bar->addMenu(tr("&Option"));

    connection = new QAction(tr("Connect"), this);
    connection->setCheckable(true);
    connect(connection, &QAction::triggered, this, &client_window::connection_func);

    exit = new QAction(tr("Exit"), this);
    exit->setCheckable(true);
    connect(exit, &QAction::triggered, this, &client_window::exit_func);

    menu->addAction(connection);
    menu->addAction(exit);

    resize(400, 400);

    list = new QListWidget();

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(message);
    hbox_1->addWidget(insert_message);

    send = new QPushButton("Send", this);
    connect(send, &QPushButton::clicked, this, &client_window::send_func);

    QVBoxLayout *VBOX = new QVBoxLayout();
    VBOX->addWidget(list);
    VBOX->addLayout(hbox_1);
    VBOX->addWidget(send);

    central_widget->setLayout(VBOX);
    central_widget->setEnabled(false);
}

void client_window::data_receive(QByteArray data)
{
    client_chat *chat_widget = new client_chat();
    chat_widget->set_message(data);

    QListWidgetItem *list_item = new QListWidgetItem();
    list_item->setSizeHint(QSize(0, 65));
    list->addItem(list_item);

    list->setItemWidget(list_item, chat_widget);
}

void client_window::connection_func()
{
    _client = new client_manager();
    connect(_client, &client_manager::connected, this, [=]()
            { central_widget->setEnabled(true); });

    connect(_client, &client_manager::disconnected, this, [=]()
            { central_widget->setEnabled(false); });

    connect(_client, &client_manager::data_receive, this, &client_window::data_receive);

    _client->connect_to_server();
}

void client_window::send_func()
{
    auto message = insert_message->text().trimmed();

    _client->send_message(message);

    client_chat *chat_widget = new client_chat();
    chat_widget->set_message(message, true);

    QListWidgetItem *list_item = new QListWidgetItem();
    list_item->setSizeHint(QSize(0, 65));
    list_item->setBackground(QColorConstants::Svg::lightblue);

    list->addItem(list_item);

    list->setItemWidget(list_item, chat_widget);

    insert_message->clear();
}

void client_window::exit_func()
{
    _client->close();
}