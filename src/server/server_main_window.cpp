#include "server_main_window.h"

server_manager *server_main_window::_server = nullptr;

QHash<QString, QWidget *> server_main_window::_window_map = QHash<QString, QWidget *>();

server_main_window::server_main_window(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent), _db_connection(db_connection)
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(400, 400);

    _tabs = new QTabWidget(this);
    _tabs->setTabsClosable(true);
    connect(_tabs, &QTabWidget::tabCloseRequested, this, &server_main_window::close_tabs);

    _status_bar = new QStatusBar(this);
    setStatusBar(_status_bar);

    _list = new QListWidget(this);
    _disconnect_all = new QPushButton("Disconnect ALL CLIENTS", this);
    connect(_disconnect_all, &QPushButton::clicked, this, [=]()
            { _server->disconnect_all_clients(); });

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(_list);
    vbox->addWidget(_disconnect_all);

    if (!_server)
        _server = new server_manager(_db_connection, this);

    connect(_server, &server_manager::new_client_connected, this, &server_main_window::on_new_client_connected);
    connect(_server, &server_manager::new_client_disconnected, this, &server_main_window::on_new_client_disconnected);

    QHBoxLayout *HBOX = new QHBoxLayout(central_widget);
    HBOX->addWidget(_tabs, 6);
    HBOX->addLayout(vbox, 3);
}

server_main_window::~server_main_window()
{
    _window_map = QHash<QString, QWidget *>();
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void server_main_window::on_new_client_connected(QTcpSocket *client)
{
    QString client_name = client->property("client_name").toString();

    server_chat_window *wid = new server_chat_window(client, this);
    _tabs->addTab(wid, client_name);

    _window_map.insert(client_name, wid);

    _list->addItem(QString("%1 is connected").arg(client_name));

    connect(wid, &server_chat_window::client_name_changed, this, &server_main_window::on_client_name_changed);
    connect(wid, &server_chat_window::is_typing_received, this, &server_main_window::on_is_typing_received);
}

void server_main_window::on_new_client_disconnected(QTcpSocket *client)
{
    QString client_name = client->property("client_name").toString();

    _tabs->removeTab(_tabs->indexOf(_window_map.value(client_name)));

    _list->addItem(QString("%1 is disconnected").arg(client_name));
}

void server_main_window::on_client_name_changed(QString original_name, QString old_name, QString client_name)
{
    QWidget *wid = qobject_cast<QWidget *>(sender());
    int index = _tabs->indexOf(wid);

    _tabs->setTabText(index, client_name);

    QList<QListWidgetItem *> items = _list->findItems(QString("%1 is connected").arg(old_name), Qt::MatchExactly);
    if (!items.empty())
        items.first()->setText(QString("%1 is connected").arg(client_name));

    _window_map.remove(old_name);
    _window_map.insert(client_name, wid);

    _server->notify_other_clients(old_name, client_name);
}

void server_main_window::on_is_typing_received(QString sender, QString receiver)
{
    if (!receiver.compare("Server"))
        _status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000);
    else
        _server->is_typing_for_other_clients(sender, receiver);
}

void server_main_window::close_tabs(int index)
{
    server_chat_window *wid = qobject_cast<server_chat_window *>(_tabs->widget(index));
    wid->disconnect_from_host();

    _tabs->removeTab(index);
}