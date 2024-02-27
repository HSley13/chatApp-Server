#include "server_chat_window.h"
#include "chat_line.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    list = new QListWidget(this);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    connect(_socket, &QTcpSocket::readyRead, this, &server_chat_window::data_receive);
    connect(_socket, &QTcpSocket::disconnected, this, &server_chat_window::disconnecton);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

void server_chat_window::data_receive()
{
    QString message = _socket->readAll();

    chat_line *wid = new chat_line();
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);
}

void server_chat_window::send_message()
{
    QString message = insert_message->text();

    _socket->write(message.toUtf8());

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

void server_chat_window::disconnecton()
{
    send_button->setEnabled(false);
    insert_message->setEnabled(false);
}