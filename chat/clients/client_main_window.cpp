#include "client_main_window.h"
#include "client_manager.h"
#include "client_chat_window.h"
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

client_main_window::client_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);
    central_widget->setEnabled(false);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    menu = new QMenu("OPTIONS", this);

    QAction *connection = new QAction("Connect", this);
    connect(connection, &QAction::triggered, this, &client_main_window::connection);

    menu->addAction(connection);

    menu_bar->addMenu(menu);

    insert_name = new QLineEdit(this);
    insert_name->setPlaceholderText("Insert your name here");
    connect(insert_name, &QLineEdit::editingFinished, this, &client_main_window::send_name);

    list = new QListWidget(this);

    QLabel *message = new QLabel("Send Message-->Server", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &client_main_window::send_message);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(insert_name);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

void client_main_window::data_text_receive(QString message)
{
    client_chat_window *wid = new client_chat_window();
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);
}

void client_main_window::connection()
{
    con = new client_manager();
    connect(con, &client_manager::connected, this, [=]()
            { central_widget->setEnabled(true); });

    connect(con, &client_manager::disconnected, this, [=]()
            { central_widget->setEnabled(false); });

    connect(con, &client_manager::text_message_received, this, &client_main_window::data_text_receive);
    connect(con, &client_manager::is_typing_received, this, &client_main_window::set_is_typing);

    connect(insert_message, &QLineEdit::textChanged, con, &client_manager::send_is_typing);

    con->connect_to_server();

    status_bar->showMessage("Connected to the Server", 7500);
}

void client_main_window::send_message()
{
    QString message = insert_message->text();

    con->send_text(message);

    client_chat_window *wid = new client_chat_window();
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setSizeHint(QSize(0, 65));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

    list->addItem(line);
    list->setItemWidget(line, wid);

    insert_message->clear();
}

void client_main_window::send_name()
{
    QString name = insert_name->text();

    con->send_name(name);
}

void client_main_window::set_is_typing()
{
    status_bar->showMessage("Serving is typing...", 1000);
}