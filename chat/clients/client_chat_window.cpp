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

client_manager *client_chat_window::_client = nullptr;

client_chat_window::client_chat_window(QWidget *parent)
    : QMainWindow(parent)
{
    set_up_window();

    connect(insert_name, &QLineEdit::editingFinished, this, &client_chat_window::send_name);
    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message);

    connect(insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing);

    connect(_client, &client_manager::disconnected_from, this, &client_chat_window::on_client_disconnected);
}

client_chat_window::client_chat_window(QString destinator, QWidget *parent)
    : QMainWindow(parent), _destinator(destinator)
{
    set_up_window();

    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message_client);

    connect(insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing_client);
}

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

void client_chat_window::send_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(file_name);

        file_name.clear();
    }
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

void client_chat_window::send_name()
{
    QString name = insert_name->text();

    _client->send_name(name);
}

void client_chat_window::on_is_typing_received(QString sender)
{
    emit is_typing_received(sender);
}

void client_chat_window::init_receiving_file(QString client_name, QString file_name, qint64 file_size)
{
    client_name = nullptr;

    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(destinator(), file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void client_chat_window::reject_receiving_file()
{
    QMessageBox::critical(this, "File Rejected", "Sending File Rejected");
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

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);

    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void client_chat_window::on_client_connected(QString client_name)
{
    emit client_connected(client_name);
}

void client_chat_window::on_connection_ACK(QString my_name, QStringList other_clients)
{
    emit connection_ACK(my_name, other_clients);
}

void client_chat_window::on_client_name_changed(QString old_name, QString client_name)
{
    emit client_name_changed(old_name, client_name);
}

void client_chat_window::on_client_disconnected(QString client_name)
{
    emit client_disconnected(client_name, my_name());
}

const QString &client_chat_window::destinator() const
{
    return _destinator;
}

void client_chat_window::set_up_window()
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    insert_name = new QLineEdit(this);
    insert_name->setPlaceholderText("Insert your name here before doing anything");

    list = new QListWidget(this);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);

    QPushButton *file = new QPushButton(QString("Open %1 Directory").arg(destinator()), this);
    connect(file, &QPushButton::clicked, this, &client_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &client_chat_window::send_file);

    hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);
    hbox->addWidget(file);
    hbox->addWidget(send_file);

    send_button = new QPushButton("Send", this);

    VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(insert_name);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);

    if (!_client)
    {
        _client = new client_manager();
        connect(_client, &client_manager::text_message_received, this, &client_chat_window::on_text_message_received);
        connect(_client, &client_manager::is_typing_received, this, &client_chat_window::on_is_typing_received);
        connect(_client, &client_manager::init_receiving_file, this, &client_chat_window::init_receiving_file);
        connect(_client, &client_manager::reject_receiving_file, this, &client_chat_window::reject_receiving_file);
        connect(_client, &client_manager::file_saved, this, &client_chat_window::file_saved);

        connect(_client, &client_manager::client_connected, this, &client_chat_window::on_client_connected);
        connect(_client, &client_manager::connection_ACK, this, &client_chat_window::on_connection_ACK);
        connect(_client, &client_manager::client_name_changed, this, &client_chat_window::on_client_name_changed);
        connect(_client, &client_manager::client_disconnected, this, &client_chat_window::on_client_disconnected);

        _protocol = new chat_protocol(this);
    }
}

QString client_chat_window::my_name()
{
    _protocol = new chat_protocol(this);
    QString name = insert_name->text().length() > 0 ? insert_name->text() : _protocol->my_name();

    return name;
}

QString client_chat_window::name_inserted()
{
    _protocol = new chat_protocol(this);
    QString name = insert_name->text().length() > 0 ? insert_name->text() : _protocol->my_name();

    return name;
}

void client_chat_window::on_text_message_received(QString sender, QString message)
{
    emit text_message_received(sender, message);
}

void client_chat_window::send_is_typing(QString receiver)
{
    receiver = "Server";
    _client->send_is_typing(my_name(), receiver);
}

void client_chat_window::send_is_typing_client(QString receiver)
{
    receiver = nullptr;
    _client->send_is_typing(name_inserted(), destinator());
}

void client_chat_window::disconnect_client()
{
    _client->send_disconnect_client_message(my_name(), destinator());
}
