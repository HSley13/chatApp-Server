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

    insert_message = new QLineEdit(this);
    insert_message->setPlaceholderText("Insert New Message");
    connect(insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    send_button = new QPushButton("Send", this);
    connect(send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(insert_message, 7);
    hbox_1->addWidget(send_button, 3);

    QPushButton *file = new QPushButton("Open Client Directory", this);
    connect(file, &QPushButton::clicked, this, &server_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &server_chat_window::send_file);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(file, 7);
    hbox_2->addWidget(send_file, 3);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox_1);
    VBOX->addLayout(hbox_2);

    dir.mkdir(_client->name());
    dir.setPath("./" + _client->name());

    connect(_client, &server_manager::text_message_received, this, &server_chat_window::on_text_message_received);

    connect(_client, &server_manager::client_name_changed, this, &server_chat_window::on_client_name_changed);

    connect(_client, &server_manager::init_receiving_file, this, &server_chat_window::on_init_receiving_file);
    connect(_client, &server_manager::file_saved, this, &server_chat_window::on_file_saved);

    connect(_client, &server_manager::is_typing_received, this, [=](QString sender, QString receiver)
            { emit is_typing_received(sender, receiver); });

    connect(_client, &server_manager::reject_receiving_file, this, [=](QString sender)
            { QMessageBox::critical(this, "Rejection", QString("%1 has Rejected Your request to send a file").arg(sender)); });
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
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

void server_chat_window::on_init_receiving_file(QString sender, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(sender, file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);
    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void server_chat_window::on_client_name_changed(QString original_name, QString old_name, QString name)
{
    QFile::rename(dir.canonicalPath(), name);

    emit client_name_changed(original_name, old_name, name);
}

void server_chat_window::on_file_saved(QString path)
{
    QString message = QString("File save at: %1").arg(path);

    QMessageBox::information(this, "File Saved", message);
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

void server_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();

    QString full_client_directory = QDir(executable_directory).filePath(_client->name());

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);
    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void server_chat_window::disconnect_from_host()
{
    _client->disconnect_from_host();
}
