#include "server_main_window.h"

server_manager *server_main_window::_server = nullptr;
chat_protocol *server_main_window::_protocol = nullptr;

QHash<QString, QWidget *> server_main_window::_window_map = QHash<QString, QWidget *>();

class separator_delegate : public QStyledItemDelegate
{
private:
    QListWidget *m_parent;

public:
    separator_delegate(QListWidget *parent) : QStyledItemDelegate(parent), m_parent(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        if (index.row() != m_parent->count() - 1)
        {
            painter->save();
            painter->setPen(Qt::white);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
            painter->restore();
        }
    }
};

server_main_window::server_main_window(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent), _db_connection(db_connection)
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(800, 100);

    _tabs = new QTabWidget(this);
    _tabs->setTabsClosable(true);
    connect(_tabs, &QTabWidget::tabCloseRequested, this, &server_main_window::close_tabs);

    _status_bar = new QStatusBar(this);
    setStatusBar(_status_bar);

    _list = new QListWidget(this);
    _list->setItemDelegate(new separator_delegate(_list));

    _disconnect_all = new QPushButton("Disconnect ALL CLIENTS", this);
    connect(_disconnect_all, &QPushButton::clicked, this, [=]()
            { _server->disconnect_all_clients(); });

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(_list);
    vbox->addWidget(_disconnect_all);

    if (!_server && !_protocol)
    {
        _server = new server_manager(_db_connection, this);
        _protocol = new chat_protocol(this);
    }

    connect(_server, &server_manager::new_client_connected, this, &server_main_window::on_new_client_connected);
    connect(_server, &server_manager::new_client_disconnected, this, &server_main_window::on_new_client_disconnected);

    QHBoxLayout *HBOX = new QHBoxLayout(central_widget);
    HBOX->addWidget(_tabs, 7);
    HBOX->addLayout(vbox, 3);
}

server_main_window::~server_main_window()
{
    _window_map = QHash<QString, QWidget *>();
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void server_main_window::on_new_client_connected(QWebSocket *client)
{
    QString client_name = client->property("client_name").toString();

    server_chat_window *wid = new server_chat_window(client, this);
    _tabs->addTab(wid, client_name);

    _window_map.insert(client_name, wid);

    _list->addItem(QString("%1 is connected").arg(client_name));

    connect(wid, &server_chat_window::client_name_changed, this, &server_main_window::on_client_name_changed);
    connect(wid, &server_chat_window::is_typing_received, this, &server_main_window::on_is_typing_received);
}

void server_main_window::on_new_client_disconnected(QWebSocket *client)
{
    QString client_name = client->property("client_name").toString();

    _tabs->removeTab(_tabs->indexOf(_window_map.value(client_name)));

    _list->addItem(QString("%1 is disconnected").arg(client_name));
}

void server_main_window::on_client_name_changed(const QString &original_name, const QString &old_name, const QString &client_name)
{
    QWidget *wid = qobject_cast<QWidget *>(sender());
    int index = _tabs->indexOf(wid);

    _tabs->setTabText(index, client_name);

    QList<QListWidgetItem *> items = _list->findItems(QString("%1 is connected").arg(old_name), Qt::MatchExactly);
    if (!items.empty())
        items.first()->setText(QString("%1 is connected").arg(client_name));

    _window_map.remove(old_name);
    _window_map.insert(client_name, wid);
}

void server_main_window::on_is_typing_received(const QString &sender, const QString &receiver)
{
    (!receiver.compare("Server")) ? _status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000) : _server->is_typing_for_other_clients(sender, receiver);
}

void server_main_window::close_tabs(int index)
{
    server_chat_window *wid = qobject_cast<server_chat_window *>(_tabs->widget(index));
    wid->disconnect_from_host();

    _tabs->removeTab(index);
}