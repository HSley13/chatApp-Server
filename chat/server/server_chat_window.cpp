#include "server_chat_window.h"
#include "chat_line.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QApplication>
#include <QFileDialog>

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    list = new QListWidget(this);

    _protocol = new chat_protocol();
    _client = new server_manager(client);

    QPushButton *file = new QPushButton("Open Client Directory", this);
    connect(file, &QPushButton::clicked, this, &server_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &server_chat_window::send_file);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);
    hbox->addWidget(file);
    hbox->addWidget(send_file);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    connect(_client, &server_manager::disconnected, this, &server_chat_window::disconnection);
    connect(_client, &server_manager::text_message_received, this, &server_chat_window::text_message_received);
    connect(_client, &server_manager::name_changed, this, &server_chat_window::on_client_name_changed);
    connect(_client, &server_manager::init_receiving_file, this, &server_chat_window::init_receiving_file);
    connect(_client, &server_manager::file_saved, this, &server_chat_window::file_saved);
    connect(_client, &server_manager::is_typing_received, this, &server_chat_window::is_typing_received);

    connect(insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    dir = new QDir();
    dir->mkdir(_client->name());
    dir->setPath("./" + _client->name());

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
    QString message = insert_message->text();

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

void server_chat_window::send_file()
{
    static QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    _client->send_init_sending_file(file_name);
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

void server_chat_window::init_receiving_file(QString client_name, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(client_name, file_name).arg(file_size);

    static QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void server_chat_window::file_saved(QString path)
{
    QString message = QString("File save at: %1").arg(path);

    QMessageBox::information(this, "File Saved", message);
}

void server_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();

    QString client_directory = _client->name();

    QString full_client_directory = QDir(executable_directory).filePath(client_directory);

    QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);
}

void server_chat_window::on_client_name_changed(QString name)
{
    QFile::rename(dir->canonicalPath(), name);

    emit client_name_changed(name);
}