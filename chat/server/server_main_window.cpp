#include "server_main_window.h"
#include <QHBoxLayout>
#include <QStringList>

server_main_window::server_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(800, 400);

    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &server_main_window::close_tabs);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    list = new QListWidget(this);
    disconnect_all = new QPushButton("Disconnect ALL CLIENTS", this);
    connect(disconnect_all, &QPushButton::clicked, this, &server_main_window::disconnect_all_clients);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(list);
    vbox->addWidget(disconnect_all);

    _server = new server_manager();
    connect(_server, &server_manager::new_client_connected, this, &server_main_window::on_new_client_connected);
    connect(_server, &server_manager::new_client_disconnected, this, &server_main_window::on_new_client_disconnected);

    QHBoxLayout *HBOX = new QHBoxLayout(central_widget);
    HBOX->addWidget(tabs, 3);
    HBOX->addLayout(vbox);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void server_main_window::on_new_client_connected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    server_chat_window *wid = new server_chat_window(client);
    tabs->addTab(wid, QString("Client %1").arg(id));

    list->addItem(QString("Client %1 Connected").arg(id));

    connect(wid, &server_chat_window::client_name_changed, this, &server_main_window::on_client_name_changed);
    connect(wid, &server_chat_window::is_typing_received, this, &server_main_window::on_is_typing_received);

    connect(wid, &server_chat_window::text_for_other_client, _server, &server_manager::on_text_for_other_clients);
}

void server_main_window::on_new_client_disconnected(QTcpSocket *client)
{
    int id = client->property("id").toInt();

    list->addItem(QString("Client %1 disconnected").arg(id));
}

void server_main_window::disconnect_all_clients()
{
    _server->disconnect_all_clients();
}

void server_main_window::on_client_name_changed(QString old_name, QString client_name)
{
    wid = qobject_cast<QWidget *>(sender());
    int index = tabs->indexOf(wid);

    tabs->setTabText(index, client_name);

    _server->notify_other_clients(old_name, client_name);

    QMap<QString, QString>::iterator it = _server->_names.find(old_name);
    if (it != _server->_names.end())
        _server->_names.erase(it);

    _server->_names.insert(old_name, client_name);
}

void server_main_window::on_is_typing_received(QString sender, QString receiver)
{
    if (!receiver.compare("Server"))
        status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000);

    else
        _server->is_typing_for_other_clients(sender, receiver);
}

void server_main_window::close_tabs(int index)
{
    server_chat_window *wid = qobject_cast<server_chat_window *>(tabs->widget(index));
    wid->disconnect();

    tabs->removeTab(index);
}