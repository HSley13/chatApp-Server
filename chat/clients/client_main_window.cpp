#include "client_main_window.h"
#include <QAction>
#include <QLabel>

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>

QMap<QString, QWidget *> client_main_window::window_map = QMap<QString, QWidget *>();
QMap<QString, QString> client_main_window::name_list = QMap<QString, QString>();

client_main_window::client_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    resize(600, 400);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    menu = new QMenu("OPTIONS", this);

    QAction *connection = new QAction("Connect", this);
    connect(connection, &QAction::triggered, this, &client_main_window::connected);

    menu->addAction(connection);
    menu_bar->addMenu(menu);

    name = new QLineEdit(this);
    name->setPlaceholderText("INSERT YOUR NAME HERE THEN PRESS ENTER");
    name->setDisabled(true);
    connect(name, &QLineEdit::returnPressed, this, &client_main_window::on_name_changed);

    tabs = new QTabWidget(this);
    tabs->setDisabled(true);
    tabs->setTabsClosable(true);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &client_main_window::close_tabs);

    VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(name);
    VBOX->addWidget(tabs);
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
    connect(wid, &client_chat_window::socket_disconnected, this, &client_main_window::on_socket_disconnected);

    tabs->addTab(wid, "Server");

    window_map.insert("Server", wid);

    name->setEnabled(true);

    status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::close_tabs(int index)
{
    QMap<QString, QWidget *>::iterator it = window_map.find(tabs->tabText(index));
    if (it != window_map.end())
        window_map.erase(it);

    tabs->removeTab(index);
}

void client_main_window::on_is_typing_received(QString sender)
{
    status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000);
}

void client_main_window::on_name_changed()
{
    if (!name->text().isEmpty())
    {
        tabs->setEnabled(true);

        for (QWidget *win : window_map)
        {
            client_chat_window *wid = qobject_cast<client_chat_window *>(win);
            wid->set_name(name->text());
        }
    }
}

void client_main_window::on_socket_disconnected()
{
    central_widget->setDisabled(true);

    status_bar->showMessage("The SERVER DISCONNECTED YOU", 999999);
}

void client_main_window::on_client_connected(QString client_name)
{
    client_chat_window *wid = new client_chat_window(client_name, this);

    tabs->addTab(wid, client_name);

    name_list.insert(client_name, client_name);

    window_map.insert(client_name, wid);
}

void client_main_window::on_clients_list(QString my_name, QMap<QString, QString> other_clients)
{
    for (QString client_name : other_clients)
    {
        if (client_name.compare(my_name))
        {
            client_chat_window *wid = new client_chat_window(other_clients.key(client_name), this);
            tabs->addTab(wid, client_name);

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
        tabs->widget(tabs->indexOf(win))->setDisabled(true);

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
            wid->message_received(message);

        else
            qDebug() << "client_main_window ---> on_text_message_received --> ERROR CASTING THE WIDGET:";
    }
    else
    {
        client_chat_window *wid = new client_chat_window(name_list.key(sender), this);

        if (wid)
        {
            wid->message_received(message);

            tabs->addTab(wid, sender);

            window_map.insert(sender, wid);
        }
    }
}

void client_main_window::on_client_name_changed(QString old_name, QString client_name)
{
    QWidget *win = window_map.value(old_name);

    if (win)
    {
        tabs->setTabText(tabs->indexOf(win), client_name);

        window_map.insert(client_name, win);
        window_map.remove(old_name);

        name_list.insert(old_name, client_name);
    }
    else
        qDebug() << "client_name to change not FOUND";
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
