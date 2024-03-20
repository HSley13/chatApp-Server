#include "client_main_window.h"
#include "client_manager.h"
#include "client_chat_window.h"
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

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

    QPushButton *file = new QPushButton("...", this);
    connect(file, &QPushButton::clicked, this, &client_main_window::send_file);

    hbox->addWidget(message);
    hbox->addWidget(insert_message);
    hbox->addWidget(file);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &client_main_window::send_message);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(insert_name);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

void client_main_window::connection()
{
    _client = new client_manager();
    connect(_client, &client_manager::connected, this, [=]()
            { central_widget->setEnabled(true); });

    connect(_client, &client_manager::disconnected, this, [=]()
            { central_widget->setEnabled(false); });

    connect(_client, &client_manager::text_message_received, this, &client_main_window::text_message_received);
    connect(_client, &client_manager::is_typing_received, this, &client_main_window::is_typing_received);
    connect(_client, &client_manager::init_receiving_file, this, &client_main_window::init_receiving_file);
    connect(_client, &client_manager::reject_receiving_file, this, &client_main_window::reject_receiving_file);

    connect(insert_message, &QLineEdit::textChanged, _client, &client_manager::send_is_typing);

    _client->connect_to_server();

    status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::send_message()
{
    QString message = insert_message->text();

    _client->send_text(message);

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

void client_main_window::send_file()
{
    static QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    _client->send_init_sending_file(file_name);
}

void client_main_window::text_message_received(QString message)
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

void client_main_window::send_name()
{
    QString name = insert_name->text();

    _client->send_name(name);
}

void client_main_window::is_typing_received()
{
    status_bar->showMessage("Serving is typing...", 1000);
}

void client_main_window::init_receiving_file(QString client_name, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(client_name, file_name).arg(file_size);

    static QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void client_main_window::reject_receiving_file()
{
    QMessageBox::critical(this, "File Rejected", "Sending File Rejected");
}