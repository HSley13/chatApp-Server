#include "client_chat_window.h"
#include "client_manager.h"

QString client_chat_window::_my_name = nullptr;
QString client_chat_window::_insert_name = nullptr;

client_manager *client_chat_window::_client = nullptr;
chat_protocol *client_chat_window::_protocol = nullptr;

sql::Connection *client_chat_window::_db_connection = nullptr;

QPoint client_chat_window::drag_start_position;
bool client_chat_window::dragging = false;

client_chat_window::client_chat_window(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent)
{
    set_up_window();

    if (!_db_connection)
        _db_connection = db_connection;

    connect(_send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file);

    connect(_client, &client_manager::file_saved, this, &client_chat_window::on_file_saved);
}

client_chat_window::client_chat_window(QString destinator, QWidget *parent)
    : QMainWindow(parent), _destinator(destinator)
{
    set_up_window();

    dir.mkdir(_destinator);
    dir.setPath("./" + _destinator);

    connect(_send_file_button, &QPushButton::clicked, this, &client_chat_window::send_file_client);

    connect(_client, &client_manager::file_client_saved, this, &client_chat_window::on_file_saved);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_chat_window::on_init_receiving_file(QString file_name, qint64 file_size)
{
    QString message = QString("-------- %1 --------\n  %2 wants to send a File. Willing to accept it or not?\n File Name: %3\n File Size: %4 bytes").arg(my_name(), "Server").arg(file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    (result == QMessageBox::Yes) ? _client->send_accept_file() : _client->send_reject_file();
}

void client_chat_window::on_init_receiving_file_client(QString sender, QString file_name, qint64 file_size)
{
    QString message = QString("-------- %1 --------\n  %2 wants to send a File. Willing to accept it or not?\n File Name: %3\n File Size: %4 bytes").arg(my_name(), sender).arg(file_name).arg(file_size);

    QMessageBox::StandardButton result = QMessageBox::question(this, "Receiving File", message);

    (result == QMessageBox::Yes) ? _client->send_accept_file_client(sender) : _client->send_reject_file_client(my_name(), sender);
}

void client_chat_window::on_file_saved(QString path)
{
    QMessageBox::information(this, "File Saved", QString("File save at: %1").arg(path));

    add_file(path, false);
}

void client_chat_window::start_recording()
{
    QMicrophonePermission microphonePermission;

    switch (qApp->checkPermission(microphonePermission))
    {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(microphonePermission, this, [=]()
                                { qDebug() << "Undetermined: Microphone permission granted!"; });

        std::cout << std::endl;
        break;

    case Qt::PermissionStatus::Denied:
        qApp->requestPermission(microphonePermission, this, [=]()
                                { qDebug() << "Asking permission within the Denied case"; });

        qWarning("Denied: Microphone permission is not granted!");
        std::cout << std::endl;
        break;

    case Qt::PermissionStatus::Granted:
        QMediaCaptureSession session;

        QAudioInput audioInput;
        session.setAudioInput(&audioInput);

        QMediaRecorder recorder;
        session.setRecorder(&recorder);

        recorder.setQuality(QMediaRecorder::HighQuality);
        recorder.setOutputLocation(QUrl::fromLocalFile("test.mp3"));
        recorder.record();
        qDebug() << "Recording started!";

        std::cout << std::endl;
        break;
    }
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/
void client_chat_window::send_message()
{
    QString message = _insert_message->text();

    _client->send_text(my_name(), _destinator, message);

    chat_line *wid = new chat_line(this);
    wid->set_message(message, true);
    wid->setStyleSheet("color: black;");

    QListWidgetItem *line = new QListWidgetItem(_list);
    line->setSizeHint(QSize(0, 60));
    line->setBackground(QBrush(QColorConstants::Svg::lightblue));

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
    line->setSizeHint(QSize(0, 60));

    _list->addItem(line);
    _list->setItemWidget(line, wid);
}

void client_chat_window::send_is_typing()
{
    _client->send_is_typing(my_name(), _destinator);
}

void client_chat_window::send_file()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");
    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file(file_name);

        connect(_client, &client_manager::file_accepted, this, [=]()
                { add_file(QFileInfo(file_name).absoluteFilePath()); });

        file_name.clear();
    }
}

void client_chat_window::send_file_client()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a File", "/home");
    if (!file_name.isEmpty())
    {
        _client->send_init_sending_file_client(my_name(), _destinator, file_name);

        connect(_client, &client_manager::file_accepted_client, this, [=]()
                { add_file(QFileInfo(file_name).absoluteFilePath()); });

        file_name.clear();
    }
}

void client_chat_window::folder()
{
    QString executable_directory = QApplication::applicationDirPath();
    QString full_client_directory = QDir(executable_directory).filePath(_window_name);

    QString selected_file_path = QFileDialog::getOpenFileName(this, "Open Directory", full_client_directory);

    QDesktopServices::openUrl(QUrl::fromLocalFile(selected_file_path));
}

void client_chat_window::set_up_window()
{
    QWidget *central_widget = new QWidget();
    setCentralWidget(central_widget);

    QPushButton *button_file = new QPushButton("Server's Conversation", this);
    button_file->setStyleSheet("border: none;");
    connect(button_file, &QPushButton::clicked, this, &client_chat_window::folder);

    connect(this, &client_chat_window::update_button_file, this, [=]()
            { button_file->setText(QString("%1's Conversation").arg(_window_name)); });

    _list = new QListWidget(this);

    _send_file_button = new QPushButton("...", this);

    _insert_message = new QLineEdit(this);
    _insert_message->setPlaceholderText("Insert New Message");
    connect(_insert_message, &QLineEdit::textChanged, this, &client_chat_window::send_is_typing);

    QPixmap image_send(":/images/send_icon.png");
    if (!image_send)
        qDebug() << "Image Send Button is NULL";

    QPushButton *send_button = new QPushButton(this);
    send_button->setIcon(image_send);
    send_button->setIconSize(QSize(30, 30));
    send_button->setFixedSize(30, 30);
    send_button->setStyleSheet("border: none");
    connect(send_button, &QPushButton::clicked, this, &client_chat_window::send_message);

    QPixmap image_record(":/images/record_icon.png");
    if (!image_record)
        qDebug() << "Image Record Button is NULL";

    QPushButton *record_button = new QPushButton(this);
    record_button->setIcon(image_record);
    record_button->setIconSize(QSize(50, 50));
    record_button->setFixedSize(50, 50);
    record_button->setStyleSheet("border: none");
    connect(record_button, &QPushButton::clicked, this, &client_chat_window::start_recording);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(_send_file_button);
    hbox->addWidget(_insert_message);
    hbox->addWidget(send_button);
    hbox->addWidget(record_button);

    QVBoxLayout *VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(button_file);
    VBOX->addWidget(_list);
    VBOX->addLayout(hbox);

    if (!_client && !_protocol)
    {
        _client = new client_manager(_db_connection, this);
        connect(_client, &client_manager::text_message_received, this, [=](QString sender, QString message)
                { emit text_message_received(sender, message); });

        connect(_client, &client_manager::is_typing_received, this, [=](QString sender)
                { emit is_typing_received(sender); });

        connect(_client, &client_manager::reject_receiving_file, this, [=]()
                { QMessageBox::critical(this, "File Rejected", QString("-------- %1 --------\n Server Rejected Your request to send the file").arg(my_name())); });

        connect(_client, &client_manager::reject_receiving_file_client, this, [=](QString sender)
                { QMessageBox::critical(this, "File Rejected", QString("-------- %1 --------\n %2 Rejected Your request to send the file").arg(my_name(), sender)); });

        connect(_client, &client_manager::client_connected, this, [=](QString client_name)
                { emit client_connected(client_name); });

        connect(_client, &client_manager::client_disconnected, this, [=](QString client_name)
                { emit client_disconnected(client_name); });

        connect(_client, &client_manager::clients_list, this, [=](QString my_name, QHash<QString, QString> other_clients)
                { emit clients_list(my_name, other_clients); });

        connect(_client, &client_manager::client_name_changed, this, [=](QString old_name, QString client_name)
                { emit client_name_changed(old_name, client_name); });

        connect(_client, &client_manager::socket_disconnected, this, [=]()
                { emit socket_disconnected(); });

        connect(_client, &client_manager::init_receiving_file, this, &client_chat_window::on_init_receiving_file);
        connect(_client, &client_manager::init_receiving_file_client, this, &client_chat_window::on_init_receiving_file_client);

        _protocol = new chat_protocol(this);
    }
}

QString client_chat_window::my_name()
{
    QString name = _insert_name.length() > 0 ? _insert_name : _protocol->my_name();

    return name;
}

void client_chat_window::set_name(QString insert_name)
{
    _insert_name = insert_name;

    _client->send_name(insert_name);
}

void client_chat_window::window_name(QString name)
{
    _window_name = name;

    emit update_button_file();

    QFile::rename(dir.canonicalPath(), name);
}

void client_chat_window::mousePressEvent(QMouseEvent *event)
{
    drag_start_position = event->pos();
    dragging = true;
}

void client_chat_window::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->button() != Qt::LeftButton))
    {
        int delta_X = event->pos().x() - drag_start_position.x();

        if (delta_X > 25)
        {
            emit swipe_right();
            dragging = false;
        }
    }
    else
        dragging = false;
}

void client_chat_window::add_file(QString path, bool is_mine)
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