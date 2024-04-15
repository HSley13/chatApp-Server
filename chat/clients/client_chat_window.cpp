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

    connect(_send_button, &QPushButton::clicked, this, &client_chat_window::send_message);

    connect(_send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file);

    connect(_insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing);

    connect(_file, &QPushButton::clicked, this, &client_chat_window::folder);
}

client_chat_window::client_chat_window(QString destinator, QWidget *parent)
    : QMainWindow(parent), _destinator(destinator)
{
    set_up_window();

    connect(_send_button, &QPushButton::clicked, this, &client_chat_window::send_message_client);

    connect(_send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file_client);

    connect(_insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing_client);

    connect(_file, &QPushButton::clicked, this, &client_chat_window::folder_client);

    dir.mkdir(_destinator);
    dir.setPath("./" + _destinator);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_chat_window::on_init_receiving_file(QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg("Server", file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);
    if (result == QMessageBox::Yes)
        _client->send_accept_file();
    else
        _client->send_reject_file();
}

void client_chat_window::on_init_receiving_file_client(QString sender, QString file_name, qint64 file_size)
{
    QString message = QString("%1 wants to send a File. Willing to accept it or not?\n File Name: %2\n File Size: %3 bytes").arg(sender, file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);
    if (result == QMessageBox::Yes)
        _client->send_accept_file_client(sender);
    else
        _client->send_reject_file_client(my_name(), sender);
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void client_chat_window::send_message()
{
    QString message = _insert_message->text();

    _client->send_text(my_name(), "Server", message);

    chat_line *wid = new chat_line(this);
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setSizeHint(QSize(0, 65));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

    _list->addItem(line);
    _list->setItemWidget(line, wid);

    _insert_message->clear();

    emit text_message_sent("Server");
}

void client_chat_window::send_message_client()
{
    QString message = _insert_message->text();

    _client->send_text(my_name(), destinator(), message);

    chat_line *wid = new chat_line(this);
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setSizeHint(QSize(0, 65));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

    _list->addItem(line);
    _list->setItemWidget(line, wid);

    _insert_message->clear();

    emit text_message_sent(_window_name);
}

void client_chat_window::message_received(QString message)
{
    chat_line *wid = new chat_line(this);
    wid->set_message(message);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem();
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 65));

    _list->addItem(line);
    _list->setItemWidget(line, wid);
}

void client_chat_window::send_is_typing()
{
    _client->send_is_typing(my_name(), "Server");
}

void client_chat_window::send_is_typing_client()
{
    _client->send_is_typing(my_name(), destinator());
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

void client_chat_window::send_file_client()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");
    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file_client(my_name(), destinator(), file_name);

        file_name.clear();
    }
}

void client_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();
    QString full_client_directory = QDir(executable_directory).filePath("Server");

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Directory", full_client_directory);
    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void client_chat_window::folder_client()
{
    QString executable_directory = QApplication::applicationDirPath();
    QString full_client_directory = QDir(executable_directory).filePath(destinator());

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Directory", full_client_directory);
    if (!selected_file_path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void client_chat_window::set_up_window()
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    _insert_message = new QLineEdit(this);
    _insert_message->setPlaceholderText("Insert New Message");

    _send_button = new QPushButton("Send", this);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(_insert_message, 7);
    hbox_1->addWidget(_send_button, 3);

    _file = new QPushButton("Open Directory", this);

    _send_file_button = new QPushButton("...", this);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(_file, 7);
    hbox_2->addWidget(_send_file_button, 3);

    _list = new QListWidget(this);

    _label = new QLabel("Server's Conversation", this);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(_label);
    VBOX->addWidget(_list);
    VBOX->addLayout(hbox_1);
    VBOX->addLayout(hbox_2);

    connect(this, &client_chat_window::update_label, this, [=]()
            { _label->setText(QString("%1's Conversation").arg(_window_name)); });

    if (!_client)
    {
        _client = new client_manager();
        connect(_client, &client_manager::text_message_received, this, [=](QString sender, QString message)
                { emit text_message_received(sender, message); });

        connect(_client, &client_manager::is_typing_received, this, [=](QString sender)
                { emit is_typing_received(sender); });

        connect(_client, &client_manager::reject_receiving_file, this, [=]()
                { QMessageBox::critical(this, "File Rejected", "Server Rejected Your request to send the file"); });

        connect(_client, &client_manager::reject_receiving_file_client, this, [=](QString sender)
                { QMessageBox::critical(this, "File Rejected", QString("%1 Rejected Your request to send the file").arg(sender)); });

        connect(_client, &client_manager::client_connected, this, [=](QString client_name)
                { emit client_connected(client_name); });

        connect(_client, &client_manager::client_disconnected, this, [=](QString client_name)
                { emit client_disconnected(client_name); });

        connect(_client, &client_manager::clients_list, this, [=](QString my_name, QMap<QString, QString> other_clients)
                { emit clients_list(my_name, other_clients); });

        connect(_client, &client_manager::client_name_changed, this, [=](QString old_name, QString client_name)
                { emit client_name_changed(old_name, client_name); });

        connect(_client, &client_manager::socket_disconnected, this, [=]()
                { emit socket_disconnected(); });

        connect(_client, &client_manager::init_receiving_file, this, &client_chat_window::on_init_receiving_file);
        connect(_client, &client_manager::init_receiving_file_client, this, &client_chat_window::on_init_receiving_file_client);

        connect(_client, &client_manager::file_saved, this, [=](QString path)
                { QMessageBox::information(this, "File Saved", QString("File save at: %1").arg(path)); });

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

    emit update_label(_label);

    QFile::rename(dir.canonicalPath(), name);
}