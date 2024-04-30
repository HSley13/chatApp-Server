#include "client_main_window.h"
#include <QAction>
#include <QLabel>

#include <QStyledItemDelegate>
#include <QPainter>
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

QMap<QString, QWidget *> client_main_window::_window_map = QMap<QString, QWidget *>();
QMap<QString, QString> client_main_window::_name_list = QMap<QString, QString>();

QStackedWidget *client_main_window::_stack = nullptr;

client_main_window::client_main_window(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent), _db_connection(db_connection)
{
    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    resize(400, 500);

    _status_bar = new QStatusBar(this);
    setStatusBar(_status_bar);

    QMenuBar *menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    QMenu *menu = new QMenu("OPTIONS", this);

    QAction *connection = new QAction("Connect", this);
    connect(connection, &QAction::triggered, this, &client_main_window::connected);

    menu->addAction(connection);
    menu_bar->addMenu(menu);

    QLabel *my_name = new QLabel("My Name: ", this);
    _name = new QLineEdit(this);
    _name->setPlaceholderText("INSERT YOUR NAME THEN PRESS ENTER");
    _name->setDisabled(true);
    connect(_name, &QLineEdit::returnPressed, this, &client_main_window::on_name_changed);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(my_name);
    hbox->addWidget(_name);

    _list = new QListWidget(this);
    _list->setSelectionMode(QAbstractItemView::SingleSelection);
    _list->setMinimumWidth(200);
    _list->setFont(QFont("Arial", 20));
    _list->setItemDelegate(new separator_delegate(_list));
    _list->setDisabled(true);
    connect(_list, &QListWidget::itemClicked, this, &client_main_window::on_item_clicked);

    _stack = new QStackedWidget(this);
    _stack->addWidget(_list);

    QLabel *chats = new QLabel("CHATS", this);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addLayout(hbox);
    VBOX->addWidget(chats);
    VBOX->addWidget(_stack);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_main_window::connected()
{
    client_chat_window *wid = new client_chat_window(_db_connection, this);
    connect(wid, &client_chat_window::client_connected, this, &client_main_window::on_client_connected);
    connect(wid, &client_chat_window::clients_list, this, &client_main_window::on_clients_list);
    connect(wid, &client_chat_window::client_name_changed, this, &client_main_window::on_client_name_changed);
    connect(wid, &client_chat_window::client_disconnected, this, &client_main_window::on_client_disconnected);
    connect(wid, &client_chat_window::text_message_received, this, &client_main_window::on_text_message_received);
    connect(wid, &client_chat_window::swipe_right, this, [=]()
            { _stack->setCurrentIndex(0); });

    connect(wid, &client_chat_window::is_typing_received, this, [=](QString sender)
            { _status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000); });

    connect(wid, &client_chat_window::socket_disconnected, this, [=]()
            { _stack->setDisabled(true); _status_bar->showMessage("SERVER DISCONNECTED YOU", 999999); });

    connect(wid, &client_chat_window::text_message_sent, this, [=](QString client_name)
            { add_on_top(client_name); });

    _list->addItem("Server");

    wid->setObjectName("Server");
    _stack->addWidget(wid);

    _window_map.insert("Server", wid);

    _name->setEnabled(true);

    _status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::on_item_clicked(QListWidgetItem *item)
{
    QString client_name = item->text();

    QWidget *wid = _stack->findChild<QWidget *>(client_name);
    if (wid)
        _stack->setCurrentIndex(_stack->indexOf(wid));
    else
        qDebug() << "client_main_window--> on_item_clicked()--> window to forward not FOUND: " << client_name;
}

void client_main_window::on_name_changed()
{
    if (!_name->text().isEmpty())
    {
        _list->setEnabled(true);

        for (QWidget *win : _window_map)
        {
            client_chat_window *wid = qobject_cast<client_chat_window *>(win);
            wid->set_name(_name->text());
        }
    }
}

void client_main_window::on_client_connected(QString client_name)
{
    client_chat_window *wid = new client_chat_window(client_name, this);
    wid->window_name(client_name);

    _list->addItem(client_name);

    wid->setObjectName(client_name);
    _stack->addWidget(wid);

    _name_list.insert(client_name, client_name);
    _window_map.insert(client_name, wid);
}

void client_main_window::on_clients_list(QString my_name, QMap<QString, QString> other_clients)
{
    for (QString client_name : other_clients.values())
    {
        if (client_name.compare(my_name))
        {
            client_chat_window *wid = new client_chat_window(other_clients.key(client_name), this);
            wid->window_name(client_name);

            _list->addItem(client_name);

            wid->setObjectName(client_name);
            _stack->addWidget(wid);

            _name_list.insert(other_clients.key(client_name), client_name);
            _window_map.insert(client_name, wid);
        }
    }
}

void client_main_window::on_client_disconnected(QString client_name)
{
    QWidget *win = _window_map.value(client_name);
    if (win)
    {
        QList<QListWidgetItem *> items = _list->findItems(client_name, Qt::MatchExactly);
        if (!items.isEmpty())
            delete items.first();

        _window_map.remove(client_name);
        _name_list.remove(client_name);
    }
    else
        qDebug() << "client_main_window ---> on_client_disconnected() --> client_name to Disconnect not FOUND: " << client_name;
}

void client_main_window::on_text_message_received(QString sender, QString message)
{
    QWidget *win = _window_map.value(sender);
    if (win)
    {
        client_chat_window *wid = qobject_cast<client_chat_window *>(win);

        if (wid)
        {
            wid->message_received(message);
            add_on_top(sender);
        }

        else
            qDebug() << "client_main_window ---> on_text_message_received --> ERROR CASTING THE WIDGET:";
    }
    else
    {
        client_chat_window *wid = new client_chat_window(_name_list.key(sender), this);

        if (wid)
        {
            wid->message_received(message);
            add_on_top(sender);

            _list->addItem(sender);

            wid->setObjectName(sender);
            _stack->addWidget(wid);

            _window_map.insert(sender, wid);
        }
    }
}

void client_main_window::on_client_name_changed(QString old_name, QString client_name)
{
    QWidget *win = _window_map.value(old_name);
    if (win)
    {
        QWidget *wid = _stack->findChild<QWidget *>(old_name);
        wid->setObjectName(client_name);

        QList<QListWidgetItem *> items = _list->findItems(old_name, Qt::MatchExactly);
        if (!items.isEmpty())
        {
            QListWidgetItem *item_to_change = items.first();

            item_to_change->setText(client_name);
        }

        _window_map.remove(old_name);
        _window_map.insert(client_name, win);

        client_chat_window *wind = qobject_cast<client_chat_window *>(win);
        if (wind)
            wind->window_name(client_name);

        _name_list.remove(old_name);
        _name_list.insert(old_name, client_name);
    }
    else
        qDebug() << "client_name to change not FOUND";
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void client_main_window::add_on_top(const QString &client_name)
{
    QList<QListWidgetItem *> items = _list->findItems(client_name, Qt::MatchExactly);
    if (!items.empty())
    {
        QListWidgetItem *item_to_replace = items.first();

        _list->takeItem(_list->row(item_to_replace));
        _list->insertItem(0, item_to_replace);
    }
    else
        _list->insertItem(0, client_name);
}