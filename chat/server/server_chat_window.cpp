#include "server_chat_window.h"
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QApplication>
#include <QFileDialog>
#include <QStringList>

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    list = new QListWidget(this);

    _protocol = new chat_protocol(this);
    _client = new server_manager(client);

    QPushButton *file = new QPushButton("Open Client Directory", this);
    connect(file, &QPushButton::clicked, this, &server_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &server_chat_window::send_file);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    hbox = new QHBoxLayout();
    hbox->addWidget(message);
    hbox->addWidget(insert_message);
    hbox->addWidget(file);
    hbox->addWidget(send_file);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    connect(_client, &server_manager::disconnected, this, &server_chat_window::on_disconnected);
    connect(_client, &server_manager::text_message_received, this, &server_chat_window::on_text_message_received);
    connect(_client, &server_manager::client_name_changed, this, &server_chat_window::on_client_name_changed);
    connect(_client, &server_manager::init_receiving_file, this, &server_chat_window::on_init_receiving_file);
    connect(_client, &server_manager::file_saved, this, &server_chat_window::on_file_saved);
    connect(_client, &server_manager::is_typing_received, this, &server_chat_window::on_is_typing_received);

    connect(insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    dir.mkdir(_client->name());
    dir.setPath("./" + _client->name());

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox);
    VBOX->addWidget(send_button);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void server_chat_window::on_disconnected()
{
    central_widget->setDisabled(true);
}

void server_chat_window::send_message()
{
    QString message = insert_message->text();

    _client->send_text(message);

    wid = new chat_line();
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));
    line->setSizeHint(QSize(0, 65));

    list->addItem(line);
    list->setItemWidget(line, wid);

    insert_message->clear();
}

void server_chat_window::send_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");

    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(file_name);

        file_name.clear();
    }
}

void server_chat_window::on_text_message_received(QString sender, QString receiver, QString message)
{
    if (!receiver.compare("Server"))
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
    else
        emit text_for_other_client(sender, receiver, message);
}

void server_chat_window::on_is_typing_received(QString sender, QString receiver)
{
    emit is_typing_received(sender, receiver);
}

void server_chat_window::on_init_receiving_file(QString client_name, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(client_name, file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void server_chat_window::on_file_saved(QString path)
{
    QString message = QString("File save at: %1").arg(path);

    QMessageBox::information(this, "File Saved", message);
}

void server_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();

    QString full_client_directory = QDir(executable_directory).filePath(_client->name());

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);

    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void server_chat_window::on_client_name_changed(QString old_name, QString name)
{
    QFile::rename(dir.canonicalPath(), name);

    emit client_name_changed(old_name, name);
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void server_chat_window::disconnect()
{
    _client->disconnect_from_host();
}
