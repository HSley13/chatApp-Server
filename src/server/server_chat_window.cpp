#include "server_chat_window.h"

server_chat_window::server_chat_window(QWebSocket *client, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    _list = new QListWidget(this);
    _list->setItemDelegate(new SeparatorDelegate(_list));
    _list->setSelectionMode(QAbstractItemView::NoSelection);

    _protocol = new chat_protocol(this);
    _client = new server_manager(client, this);

    _insert_message = new QLineEdit(this);
    _insert_message->setPlaceholderText("Insert New Message");
    connect(_insert_message, &QLineEdit::textChanged, _client, &server_manager::send_is_typing);

    QPixmap image(":/images/send_icon.png");
    _send_button = new QPushButton(this);
    _send_button->setIcon(image);
    _send_button->setIconSize(QSize(30, 30));
    _send_button->setFixedSize(30, 30);
    _send_button->setStyleSheet("border: none;");
    connect(_send_button, &QPushButton::clicked, this, &server_chat_window::send_message);

    _send_file_button = new QPushButton("...", this);
    connect(_send_file_button, &QPushButton::clicked, this, &server_chat_window::send_file);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(_insert_message);
    hbox_1->addWidget(_send_button);
    hbox_1->addWidget(_send_file_button);

    _file = new QPushButton(QString("Open %1's Directory").arg(_client->name()), this);
    connect(_file, &QPushButton::clicked, this, &server_chat_window::folder);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(_file);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(_list);
    VBOX->addLayout(hbox_1);
    VBOX->addLayout(hbox_2);

    _dir.mkdir(_client->name());
    _dir.setPath("./" + _client->name());

    connect(_client, &server_manager::text_message_received, this, &server_chat_window::on_text_message_received);

    connect(_client, &server_manager::client_name_changed, this, &server_chat_window::on_client_name_changed);

    connect(_client, &server_manager::file_saved, this, [=](const QString &path, bool is_mine, const QString &time)
            { add_file(path, is_mine, time); });

    connect(_client, &server_manager::is_typing_received, this, [=](const QString &sender, const QString &receiver)
            { emit is_typing_received(sender, receiver); });
}
/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void server_chat_window::on_text_message_received(const QString &message, const QString &time)
{
    chat_line *wid = new chat_line(this);
    wid->set_message(message, false, time.split(" ").last());
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem(_list);
    line->setBackground(QBrush(QColorConstants::Svg::lightgray));
    line->setSizeHint(QSize(0, 60));

    _list->setItemWidget(line, wid);
}

void server_chat_window::on_client_name_changed(const QString &original_name, const QString &old_name, const QString &name)
{
    QFile::rename(_dir.canonicalPath(), name);

    _file->setText(QString("Open %1 Directory").arg(name));

    emit client_name_changed(original_name, old_name, name);
}

void server_chat_window::send_message()
{
    QString message = _insert_message->text();

    QString current_time = QTime::currentTime().toString("yyyy-MM-dd HH:mm:ss");

    const QString &UTC_time = QDateTime::fromString(current_time, "yyyy-MM-dd HH:mm:ss")
                                  .toUTC()
                                  .toString();
    _client->send_text(message, Account::UTC_to_timeZone(UTC_time, _client->_time_zone.value(_client->name())));

    chat_line *wid = new chat_line(this);
    wid->set_message(message, true, current_time);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem(_list);
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));
    line->setSizeHint(QSize(0, 60));

    _list->setItemWidget(line, wid);

    _insert_message->clear();
}

void server_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();

    QString full_client_directory = QDir(executable_directory).filePath(_client->name());

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Client Directory", full_client_directory);

    QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void server_chat_window::send_file()
{
    std::function<void(const QString &, const QByteArray &)> file_content_ready = [=](const QString &file_name, const QByteArray &file_data)
    {
        if (!file_name.isEmpty())
        {
            QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

            const QString &UTC_time = QDateTime::fromString(current_time, "yyyy-MM-dd HH:mm:ss")
                                          .toUTC()
                                          .toString();

            add_file(QFileInfo(file_name).absoluteFilePath(), true, current_time);

            _client->_socket->sendBinaryMessage(_protocol->set_file_message("Server", QFileInfo(file_name).fileName(), file_data, Account::UTC_to_timeZone(UTC_time, _client->_time_zone.value(_client->name()))));
        }
    };

    QFileDialog::getOpenFileContent("All files (*)", file_content_ready);
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void server_chat_window::disconnect_from_host()
{
    _client->disconnect_from_host();
}

void server_chat_window::add_file(const QString &file_name, bool is_mine, const QString &time)
{
    QWidget *wid = new QWidget();
    wid->setStyleSheet("color: black;");

    QPixmap image(":/images/file_icon.webp");

    QLabel *time_label = new QLabel(time.split(" ").last(), this);

    QPushButton *file = new QPushButton(this);
    file->setIcon(image);
    file->setIconSize(QSize(30, 30));
    file->setFixedSize(QSize(30, 30));
    file->setStyleSheet("border: none");

    connect(file, &QPushButton::clicked, this, [=]()
            { QDesktopServices::openUrl(QUrl::fromLocalFile(file_name)); });

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(file);
    vbox->addWidget(time_label, 0, Qt::AlignHCenter);

    QListWidgetItem *line = new QListWidgetItem(_list);
    line->setSizeHint(QSize(0, 80));

    QHBoxLayout *hbox = new QHBoxLayout(wid);

    if (is_mine)
    {
        hbox->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

        hbox->addLayout(vbox);

        line->setBackground(QBrush(QColorConstants::Svg::lightskyblue));
    }
    else
    {
        line->setBackground(QBrush(QColorConstants::Svg::lightgray));

        hbox->addLayout(vbox);

        hbox->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    }

    line->setSizeHint(wid->sizeHint());
    _list->setItemWidget(line, wid);
}