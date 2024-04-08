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

client_chat_window::client_chat_window(QWidget *parent)
    : QMainWindow(parent)
{
    set_up_window();

    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message);

    _client = new client_manager();
    connect(_client, &client_manager::text_message_received, this, &client_chat_window::on_text_message_received);
    connect(_client, &client_manager::is_typing_received, this, &client_chat_window::is_typing_received);
    connect(_client, &client_manager::init_receiving_file, this, &client_chat_window::init_receiving_file);
    connect(_client, &client_manager::reject_receiving_file, this, &client_chat_window::reject_receiving_file);
    connect(_client, &client_manager::file_saved, this, &client_chat_window::file_saved);

    connect(_client, &client_manager::client_connected, this, &client_chat_window::on_client_connected);
    connect(_client, &client_manager::connection_ACK, this, &client_chat_window::on_connection_ACK);
    connect(_client, &client_manager::client_name_changed, this, &client_chat_window::on_client_name_changed);
    connect(_client, &client_manager::client_disconnected, this, &client_chat_window::on_client_disconnected);

    connect(insert_message, &QLineEdit::textChanged, _client, &client_manager::send_is_typing);

    _protocol = new chat_protocol(this);
}

client_chat_window::client_chat_window(QString destinator, QWidget *parent)
    : QMainWindow(parent), _destinator(destinator)
{
    set_up_window();
    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message_client);
}

client_chat_window::~client_chat_window()
{
    delete central_widget;
    delete hbox;
    delete wid;
    delete line;
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

    qDebug() << "Done Setting message";
}

void client_chat_window::send_name()
{
    QString name = insert_name->text();

    _client->send_name(name);
}

void client_chat_window::is_typing_received()
{
    status_bar->showMessage("Serving is typing...", 1000);
}

void client_chat_window::init_receiving_file(QString client_name, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg("Server", file_name).arg(file_size);

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
    qDebug() << "client_chat_window-->emitting client_connected";
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
    emit client_disconnected(client_name);
}

const QString &client_chat_window::destinator() const
{
    return _destinator;
}

void client_chat_window::set_up_window()
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    insert_name = new QLineEdit(this);
    insert_name->setPlaceholderText("Insert your name here");
    connect(insert_name, &QLineEdit::editingFinished, this, &client_chat_window::send_name);

    list = new QListWidget(this);

    QLabel *message = new QLabel("Send Message-->Server", this);
    insert_message = new QLineEdit(this);
    hbox = new QHBoxLayout();

    QPushButton *file = new QPushButton("Open Server Directory", this);
    connect(file, &QPushButton::clicked, this, &client_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &client_chat_window::send_file);

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
}

QString client_chat_window::my_name()
{
    QString name = insert_name->text().length() > 0 ? insert_name->text() : _protocol->my_name();

    return name;
}

void client_chat_window::on_text_message_received(QString sender, QString message)
{
    emit text_message_received(sender, message);
    qDebug() << "client_chat_window-->emitting text_message_received()";
}