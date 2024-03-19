#include "server_chat_window.h"
#include "chat_line.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    list = new QListWidget(this);

    _protocol = new chat_protocol();
    _client = new server_manager(client, this);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    connect(_client, &server_manager::disconnected, this, &server_chat_window::disconnection);
    connect(_client, &server_manager::text_message_received, this, &server_chat_window::text_message_received);
    connect(_client, &server_manager::name_changed, this, &server_chat_window::client_name_changed);
    connect(_client, &server_manager::is_typing_received, this, &server_chat_window::is_typing_received);
    connect(insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

void server_chat_window::disconnection()
{
    send_button->setEnabled(false);
    insert_message->setEnabled(false);
}

void server_chat_window::send_message()
{
    QString message = insert_message->text().trimmed();

    _client->send_text(message);

    chat_line *wid = new chat_line();
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);

    insert_message->clear();
}

void server_chat_window::text_message_received(QString message)
{
    chat_line *wid = new chat_line();
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);
}

void server_chat_window::is_typing_received()
{
    emit is_typing(_client->name());
}
