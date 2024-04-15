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

QMap<QString, QWidget *> client_main_window::window_map = QMap<QString, QWidget *>();
QMap<QString, QString> client_main_window::name_list = QMap<QString, QString>();

QStackedWidget *client_main_window::stack = nullptr;

client_main_window::client_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    resize(400, 500);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    menu = new QMenu("OPTIONS", this);

    QAction *connection = new QAction("Connect", this);
    connect(connection, &QAction::triggered, this, &client_main_window::connected);

    menu->addAction(connection);
    menu_bar->addMenu(menu);

    back_button = new QPushButton("←", this);
    back_button->setFixedSize(30, 30);
    back_button->setStyleSheet(" font-size: 20px; ");
    connect(back_button, &QPushButton::clicked, this, [=]()
            { stack->setCurrentIndex(0); });

    QLabel *my_name = new QLabel("My Name: ", this);
    name = new QLineEdit(this);
    name->setPlaceholderText("INSERT YOUR NAME THEN PRESS ENTER");
    name->setDisabled(true);
    connect(name, &QLineEdit::returnPressed, this, &client_main_window::on_name_changed);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(back_button);
    hbox->addWidget(my_name);
    hbox->addWidget(name);

    list = new QListWidget(this);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setMinimumWidth(200);
    list->setFont(QFont("Arial", 20));
    connect(list, &QListWidget::itemClicked, this, &client_main_window::on_item_clicked);
    list->setDisabled(true);

    separator_delegate *delegate = new separator_delegate(list);
    list->setItemDelegate(delegate);

    stack = new QStackedWidget(this);
    stack->addWidget(list);

    QLabel *chats = new QLabel("CHATS", this);

    VBOX = new QVBoxLayout(central_widget);
    VBOX->addLayout(hbox);
    VBOX->addWidget(chats);
    VBOX->addWidget(stack);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_main_window::connected()
{
    client_chat_window *wid = new client_chat_window(this);
    connect(wid, &client_chat_window::client_connected, this, &client_main_window::on_client_connected);
    connect(wid, &client_chat_window::clients_list, this, &client_main_window::on_clients_list);
    connect(wid, &client_chat_window::client_name_changed, this, &client_main_window::on_client_name_changed);
    connect(wid, &client_chat_window::client_disconnected, this, &client_main_window::on_client_disconnected);
    connect(wid, &client_chat_window::text_message_received, this, &client_main_window::on_text_message_received);
    connect(wid, &client_chat_window::is_typing_received, this, &client_main_window::on_is_typing_received);
    connect(wid, &client_chat_window::socket_disconnected, this, [=]()
            { stack->setDisabled(true); status_bar->showMessage("SERVER DISCONNECTED YOU", 999999); });
    connect(wid, &client_chat_window::text_message_sent, this, [=](QString client_name)
            { add_on_top(client_name); });

    list->addItem("Server");

    wid->setObjectName("Server");
    stack->addWidget(wid);

    window_map.insert("Server", wid);

    name->setEnabled(true);

    status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::on_item_clicked(QListWidgetItem *item)
{
    QString client_name = item->text();

    QWidget *wid = stack->findChild<QWidget *>(client_name);

    if (wid)
        stack->setCurrentIndex(stack->indexOf(wid));

    else
        qDebug() << "client_main_window--> on_item_clicked()--> window to forward not FOUND: " << client_name;
}

void client_main_window::on_is_typing_received(QString sender)
{
    status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000);
}

void client_main_window::on_name_changed()
{
    if (!name->text().isEmpty())
    {
        list->setEnabled(true);

        for (QWidget *win : window_map)
        {
            client_chat_window *wid = qobject_cast<client_chat_window *>(win);
            wid->set_name(name->text());
        }
    }
}

void client_main_window::on_client_connected(QString client_name)
{
    client_chat_window *wid = new client_chat_window(client_name, this);
    wid->window_name(client_name);

    list->addItem(client_name);

    wid->setObjectName(client_name);
    stack->addWidget(wid);

    name_list.insert(client_name, client_name);

    window_map.insert(client_name, wid);
}

void client_main_window::on_clients_list(QString my_name, QMap<QString, QString> other_clients)
{
    for (QString client_name : other_clients.values())
    {
        if (client_name.compare(my_name))
        {
            client_chat_window *wid = new client_chat_window(other_clients.key(client_name), this);
            wid->window_name(client_name);

            list->addItem(client_name);

            wid->setObjectName(client_name);
            stack->addWidget(wid);

            name_list.insert(other_clients.key(client_name), client_name);

            window_map.insert(client_name, wid);
        }
    }
}

void client_main_window::on_client_disconnected(QString client_name)
{
    QWidget *win = window_map.value(client_name);

    if (win)
    {
        QList<QListWidgetItem *> items = list->findItems(client_name, Qt::MatchExactly);
        if (!items.isEmpty())
        {
            QListWidgetItem *item_to_remove = items.first();

            delete item_to_remove;
        }

        QMap<QString, QWidget *>::iterator it = window_map.find(client_name);
        if (it != window_map.end())
            window_map.erase(it);

        name_list.remove(client_name);
    }
    else
        qDebug() << "client_main_window ---> on_client_disconnected() --> client_name to Disconnect not FOUND: " << client_name;
}

void client_main_window::on_text_message_received(QString sender, QString message)
{
    QWidget *win = window_map.value(sender);
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
        client_chat_window *wid = new client_chat_window(name_list.key(sender), this);

        if (wid)
        {
            wid->message_received(message);
            add_on_top(sender);

            list->addItem(sender);

            wid->setObjectName(sender);
            stack->addWidget(wid);

            window_map.insert(sender, wid);
        }
    }
}

void client_main_window::on_client_name_changed(QString old_name, QString client_name)
{
    QWidget *win = window_map.value(old_name);
    if (win)
    {
        QWidget *wid = stack->findChild<QWidget *>(old_name);
        wid->setObjectName(client_name);

        QList<QListWidgetItem *> items = list->findItems(old_name, Qt::MatchExactly);
        if (!items.isEmpty())
        {
            QListWidgetItem *item_to_change = items.first();

            item_to_change->setText(client_name);
        }

        QMap<QString, QWidget *>::iterator it = window_map.find(old_name);
        if (it != window_map.end())
            window_map.erase(it);

        window_map.insert(client_name, win);

        client_chat_window *wind = qobject_cast<client_chat_window *>(win);
        if (wind)
            wind->window_name(client_name);

        name_list.insert(old_name, client_name);
    }
    else
        qDebug() << "client_name to change not FOUND";
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void client_main_window::add_on_top(const QString &client_name)
{
    QList<QListWidgetItem *> items = list->findItems(client_name, Qt::MatchExactly);
    if (!items.empty())
    {
        QListWidgetItem *item_to_replace = list->findItems(client_name, Qt::MatchExactly).first();
        list->takeItem(list->row(item_to_replace));
        list->insertItem(0, item_to_replace);
    }
    else
    {
        list->insertItem(0, client_name);
        qDebug() << "client_main_window--> add_on_top()--> client_name not FOUND: " << client_name;
    }
}