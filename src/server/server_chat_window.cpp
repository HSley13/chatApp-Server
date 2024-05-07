#include "server_chat_window.h"

server_chat_window::server_chat_window(QTcpSocket *client, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    _list = new QListWidget(this);

    _protocol = new chat_protocol(this);
    _client = new server_manager(client, this);

    _insert_message = new QLineEdit(this);
    _insert_message->setPlaceholderText("Insert New Message");
    connect(_insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    QPixmap image(":/s_images/send_icon.png");
    if (!image)
        qDebug() << "Image is NULL";

    _send_button = new QPushButton(this);
    _send_button->setIcon(image);
    _send_button->setIconSize(QSize(30, 30));
    _send_button->setFixedSize(30, 30);
    _send_button->setStyleSheet("border: none");
    connect(_send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(_insert_message, 7);
    hbox_1->addWidget(_send_button, 3);

    _file = new QPushButton("Open Client Directory", this);
    connect(_file, &QPushButton::clicked, this, &server_chat_window::folder);

    QPushButton *send_file = new QPushButton("...", this);
    connect(send_file, &QPushButton::clicked, this, &server_chat_window::send_file);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(_file, 7);
    hbox_2->addWidget(send_file, 3);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(_list);
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
        chat_line *wid = new chat_line(this);
        wid->set_message(message);
        wid->setStyleSheet("color: black;");

        QListWidgetItem *line = new QListWidgetItem(_list);
        line->setBackground(QBrush(QColorConstants::Svg::lightgray));
        line->setSizeHint(QSize(0, 60));

        _list->setItemWidget(line, wid);
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

    _file->setText(QString("Open %1 Directory").arg(name));

    emit client_name_changed(original_name, old_name, name);
}

void server_chat_window::on_file_saved(QString path)
{
    QString message = QString("File save at: %1").arg(path);

    QMessageBox::information(this, "File Saved", message);

    add_file(path, false);
}

void server_chat_window::send_message()
{
    QString message = _insert_message->text();

    _client->send_text(message);

    chat_line *wid = new chat_line(this);
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem(_list);
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));
    line->setSizeHint(QSize(0, 60));

    _list->setItemWidget(line, wid);

    _insert_message->clear();
}

void server_chat_window::send_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");
    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(file_name);

        connect(_client, &server_manager::file_accepted, this, [=]()
                { add_file(QFileInfo(file_name).absoluteFilePath()); });

        file_name.clear();
    }
}

void server_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();

    QString full_client_directory = QDir(executable_directory).filePath(_client->name());

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);

    QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_chat_window::disconnect_from_host()
{
    _client->disconnect_from_host();
}

void server_chat_window::add_file(QString path, bool is_mine)
{
    QPixmap image(":/images/file_icon.webp");
    if (!image)
        qDebug() << "File Image is NULL";

    QPushButton *file = new QPushButton(_protocol->file_name(), this);
    file->setIcon(image);
    file->setIconSize(QSize(60, 60));
    file->setFixedSize(QSize(60, 60));
    file->setStyleSheet("border: none");
    file->connect(file, &QPushButton::clicked, this, [=]()
                  { QDesktopServices::openUrl(QUrl::fromLocalFile(path)); });

    QListWidgetItem *item = new QListWidgetItem(_list);
    item->setSizeHint(QSize(0, 60));

    (is_mine) ? item->setBackground(QBrush(QColorConstants::Svg::lightblue)) : item->setBackground(QBrush(QColorConstants::Svg::lightgray));

    _list->setItemWidget(item, file);
}