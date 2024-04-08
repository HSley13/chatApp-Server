#include "client_main_window.h"
#include <QAction>
#include <QLabel>

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>

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
    connect(connection, &QAction::triggered, this, &client_main_window::connection);

    menu->addAction(connection);
    menu_bar->addMenu(menu);

    tabs = new QTabWidget(this);
    tabs->setEnabled(false);

    VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(tabs);
}

client_main_window::~client_main_window()
{
    delete central_widget;
}

void client_main_window::connection()
{
    client_chat_window *wid = new client_chat_window(this);
    connect(wid, &client_chat_window::client_connected, this, &client_main_window::on_client_connected);
    connect(wid, &client_chat_window::connection_ACK, this, &client_main_window::on_connection_ACK);
    connect(wid, &client_chat_window::client_name_changed, this, &client_main_window::on_client_name_changed);
    connect(wid, &client_chat_window::client_disconnected, this, &client_main_window::on_client_disconnected);
    connect(wid, &client_chat_window::text_message_received, this, &client_main_window::text_message_received);

    tabs->addTab(wid, "Server");

    window_map.insert("Server", wid);

    tabs->setEnabled(true);

    status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::on_client_connected(QString client_name)
{
    client_chat_window *wid = new client_chat_window(client_name, this);
    tabs->addTab(wid, client_name);

    window_map.insert(client_name, wid);

    tabs->setEnabled(true);

    qDebug() << "client_main_window-->setting new window";
}

void client_main_window::on_connection_ACK(QString my_name, QStringList other_clients)
{
    for (QString client_name : other_clients)
    {
        if (client_name != my_name)
        {
            client_chat_window *wid = new client_chat_window(client_name, this);
            tabs->addTab(wid, client_name);

            window_map.insert(client_name, wid);
        }
    }
}

void client_main_window::on_client_disconnected(QString client_name)
{
    QWidget *win = window_map.value(client_name);

    if (win)
        tabs->removeTab(tabs->indexOf(win));

    else
        qDebug() << "Deleting window FAILED";
}

void client_main_window::text_message_received(QString sender, QString message)
{

    QWidget *win = window_map.value(sender);
    if (win)
    {
        client_chat_window *wid = qobject_cast<client_chat_window *>(win);

        if (wid)
        {
            wid->message_received(message);

            return;
        }
    }
    else
        qDebug() << "Adding message to Window FAILED";
}

void client_main_window::on_client_name_changed(QString old_name, QString client_name)
{

    QWidget *win = window_map.value(old_name);

    if (win)
        tabs->setTabText(tabs->indexOf(win), client_name);

    else
        qDebug() << "Deleting window FAILED";
}
