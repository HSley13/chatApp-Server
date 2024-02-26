#include "chat_window.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

chat_window::chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _client(client)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(400, 400);

    list = new QListWidget();

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(message);
    hbox_1->addWidget(insert_message);

    send = new QPushButton("Send", this);
    connect(send, &QPushButton::clicked, this, &chat_window::send_func);

    connect(_client, &QTcpSocket::readyRead, this, &chat_window::data_receive);
    connect(_client, &QTcpSocket::disconnected, this, &chat_window::client_disconnected);

    QVBoxLayout *VBOX = new QVBoxLayout();
    VBOX->addWidget(list);
    VBOX->addLayout(hbox_1);
    VBOX->addWidget(send);

    central_widget->setLayout(VBOX);
}

void chat_window::data_receive()
{
    QString data = _client->readAll();
    list->addItem(data);
}

void chat_window::send_func()
{
    _client->write(insert_message->text().trimmed().toUtf8());

    list->addItem(insert_message->text());

    insert_message->clear();
}

void chat_window::client_disconnected()
{
    send->setEnabled(false);
}