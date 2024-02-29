#include "server_chat_window.h"
#include "chat_line.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

// Define static member variables
QListWidget *server_chat_window::list = nullptr;
QStatusBar *server_chat_window::status_bar = nullptr;

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent), _socket(client)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    list = new QListWidget(this);

    _protocol = new chat_protocol();

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    connect(_socket, &QTcpSocket::readyRead, this, &server_chat_window::data_receive);
    connect(_socket, &QTcpSocket::disconnected, this, &server_chat_window::disconnecton);

    connect(insert_message, &QLineEdit::textChanged, this, &server_chat_window::send_is_typing);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

void server_chat_window::data_receive()
{
    QTcpSocket *envoyeur = qobject_cast<QTcpSocket *>(sender());
    QByteArray data = _socket->readAll();

    _protocol->laod_data(data);

    switch (_protocol->G_type())
    {
    case chat_protocol::text:
        server_chat_window::text_message(_protocol->G_message());

        break;

    case chat_protocol::is_typing:
        server_chat_window::is_typing();

        break;

        // case chat_protocol::set_name:
        //     emit set_name_received(_protocol->G_set_name(), envoyeur);

        break;

    default:
        break;
    }
}

void server_chat_window::text_message(QString message)
{
    chat_line *wid = new chat_line();
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    server_chat_window::list->addItem(line);
    server_chat_window::list->setItemWidget(line, wid);
}

void server_chat_window::is_typing()
{
    status_bar->showMessage("Client is typing");
}

void server_chat_window::send_message()
{
    QString message = insert_message->text();

    _socket->write(_protocol->text_message(message));

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

void server_chat_window::send_is_typing()
{
    _socket->write(_protocol->is_typing_func());
}

void server_chat_window::disconnecton()
{
    send_button->setEnabled(false);
    insert_message->setEnabled(false);
}