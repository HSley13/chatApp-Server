#include "client_chat_window.h"
#include "client_manager.h"
#include <QAction>
#include <QLabel>

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>

QString client_chat_window::_my_name = nullptr;
QString client_chat_window::_insert_name = nullptr;

client_manager *client_chat_window::_client = nullptr;
chat_protocol *client_chat_window::_protocol = nullptr;

client_chat_window::client_chat_window(QWidget *parent)
    : QMainWindow(parent)
{
    set_up_window();

    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message);

    connect(send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file);

    connect(insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing);
}

client_chat_window::client_chat_window(QString destinator, QWidget *parent)
    : QMainWindow(parent), _destinator(destinator)
{
    set_up_window();

    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message_client);

    connect(send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file_client);

    connect(insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing_client);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_chat_window::on_text_message_received(QString sender, QString message)
{
    emit text_message_received(sender, message);
}

void client_chat_window::on_is_typing_received(QString sender)
{
    emit is_typing_received(sender);
}

void client_chat_window::on_init_receiving_file(QString sender, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(sender, file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    if (result == QMessageBox::Yes)
        _client->send_accept_file(sender, _protocol->port());
    else
        _client->send_reject_file(my_name(), sender);
}

void client_chat_window::on_reject_receiving_file()
{
    QMessageBox::critical(this, "File Rejected", "Sending File Rejected");
}

void client_chat_window::on_client_connected(QString client_name)
{
    emit client_connected(client_name);
}

void client_chat_window::on_client_disconnected(QString client_name)
{
    emit client_disconnected(client_name);
}

void client_chat_window::on_clients_list(QString my_name, QMap<QString, QString> other_clients)
{
    emit clients_list(my_name, other_clients);
}

void client_chat_window::on_client_name_changed(QString old_name, QString client_name)
{
    emit client_name_changed(old_name, client_name);
}

void client_chat_window::on_socket_disconnected()
{
    emit socket_disconnected();
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void client_chat_window::send_message()
{
    QString message = insert_message->text();

    _client->send_text(my_name(), "Server", message);

    wid = new chat_line();
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    line = new QListWidgetItem();
    line->setSizeHint(QSize(0, 65));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

    list->addItem(line);
    list->setItemWidget(line, wid);

    insert_message->clear();
}

void client_chat_window::send_message_client()
{
    QString message = insert_message->text();

    _client->send_text(my_name(), destinator(), message);

    wid = new chat_line();
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    line = new QListWidgetItem();
    line->setSizeHint(QSize(0, 65));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

    list->addItem(line);
    list->setItemWidget(line, wid);

    insert_message->clear();
}

void client_chat_window::message_received(QString message)
{
    wid = new chat_line();
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);
}

void client_chat_window::send_is_typing(QString receiver)
{
    receiver = "Server";
    _client->send_is_typing(my_name(), receiver);
}

void client_chat_window::send_is_typing_client(QString receiver)
{
    receiver = nullptr;
    _client->send_is_typing(my_name(), destinator());
}

void client_chat_window::send_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(my_name(), "Server", file_name);

        file_name.clear();
    }
}

void client_chat_window::send_file_client()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(my_name(), destinator(), file_name);

        file_name.clear();
    }
}

void client_chat_window::file_saved(QString path)
{
    QString message = QString("File save at: %1").arg(path);

    QMessageBox::information(this, "File Saved", message);
}

void client_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();
    QString full_client_directory = QDir(executable_directory).filePath("Server");

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Directory", full_client_directory);

    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void client_chat_window::set_up_window()
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    resize(400, 600);

    insert_message = new QLineEdit(this);
    insert_message->setPlaceholderText("Insert New Message");

    send_button = new QPushButton("Send", this);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(insert_message, 7);
    hbox_1->addWidget(send_button, 3);

    QPushButton *file = new QPushButton("Open Directory", this);
    connect(file, &QPushButton::clicked, this, &client_chat_window::folder);

    send_file_button = new QPushButton("...", this);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(file, 7);
    hbox_2->addWidget(send_file_button, 3);

    list = new QListWidget(this);

    label = new QLabel("Server's Conversation", this);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(label);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox_1);
    VBOX->addLayout(hbox_2);

    connect(this, &client_chat_window::update_label, this, &client_chat_window::on_update_label);

    if (!_client)
    {
        _client = new client_manager();
        connect(_client, &client_manager::text_message_received, this, &client_chat_window::on_text_message_received);
        connect(_client, &client_manager::is_typing_received, this, &client_chat_window::on_is_typing_received);
        connect(_client, &client_manager::init_receiving_file, this, &client_chat_window::on_init_receiving_file);
        connect(_client, &client_manager::reject_receiving_file, this, &client_chat_window::on_reject_receiving_file);

        connect(_client, &client_manager::file_saved, this, &client_chat_window::file_saved);

        connect(_client, &client_manager::client_connected, this, &client_chat_window::on_client_connected);
        connect(_client, &client_manager::clients_list, this, &client_chat_window::on_clients_list);
        connect(_client, &client_manager::client_name_changed, this, &client_chat_window::on_client_name_changed);
        connect(_client, &client_manager::client_disconnected, this, &client_chat_window::on_client_disconnected);

        connect(_client, &client_manager::socket_disconnected, this, &client_chat_window::on_socket_disconnected);

        _protocol = new chat_protocol(this);
    }
}

QString client_chat_window::my_name()
{
    QString name = _insert_name.length() > 0 ? _insert_name : _protocol->my_name();

    return name;
}

const QString &client_chat_window::destinator() const
{
    return _destinator;
}

void client_chat_window::set_name(QString insert_name)
{
    _insert_name = insert_name;

    _client->send_name(insert_name);
}

void client_chat_window::window_name(QString name)
{
    _window_name = name;

    emit update_label(label);
}

void client_chat_window::on_update_label(QLabel *label)
{
    label->setText(QString("%1's Conversation").arg(_window_name));
}