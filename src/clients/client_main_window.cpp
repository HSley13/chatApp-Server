#include "client_main_window.h"

QHash<QString, QWidget *> client_main_window::_window_map = QHash<QString, QWidget *>();
QHash<QString, QString> client_main_window::_name_list = QHash<QString, QString>();

QStackedWidget *client_main_window::_stack = nullptr;

client_chat_window *client_main_window::_server_wid = nullptr;

QPoint client_main_window::drag_start_position;
bool client_main_window::dragging = false;

class separator_delegate : public QStyledItemDelegate
{
private:
    QListWidget *m_parent;

public:
    separator_delegate(QListWidget *parent) : QStyledItemDelegate(parent), m_parent(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        if (index.row() != m_parent->count() - 1)
        {
            painter->save();
            painter->setPen(Qt::white);
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
            painter->restore();
        }
    }
};

client_main_window::client_main_window(sql::Connection *db_connection, QWidget *parent)
    : QMainWindow(parent), _db_connection(db_connection)
{
    _stack = new QStackedWidget(this);

    setCentralWidget(_stack);
    setFixedSize(400, 500);

    _status_bar = new QStatusBar(this);
    setStatusBar(_status_bar);

    connect(this, &client_main_window::swipe_right, this, &client_main_window::on_swipe_right);

    /*-----------------------------------¬------------------------------------------------------------------------------------------------------------------------------------*/

    QWidget *login_widget = new QWidget();

    QLabel *id_label = new QLabel("Enter Your ID: ", login_widget);
    _user_ID = new QLineEdit(login_widget);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(id_label);
    hbox->addWidget(_user_ID);

    QLabel *password_label = new QLabel("Enter your Password: ", this);
    _user_password = new QLineEdit(this);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(password_label);
    hbox_1->addWidget(_user_password);

    QPushButton *log_in = new QPushButton("Log In", login_widget);
    connect(log_in, &QPushButton::clicked, this, &client_main_window::connected);

    QVBoxLayout *VBOX = new QVBoxLayout();
    VBOX->addLayout(hbox);
    VBOX->addLayout(hbox_1);
    VBOX->addWidget(log_in);

    QGroupBox *group_box = new QGroupBox("Log In System");
    group_box->setLayout(VBOX);

    QPushButton *sign_in = new QPushButton("Sign In", this);
    connect(sign_in, &QPushButton::clicked, this, [=]()
            { _stack->setCurrentIndex(1); });

    QGridLayout *grid = new QGridLayout(login_widget);
    grid->addWidget(group_box, 0, 0, 1, 1, Qt::AlignCenter);
    grid->addWidget(sign_in, 1, 0, 1, 1, Qt::AlignBottom | Qt::AlignLeft);

    /*-----------------------------------¬------------------------------------------------------------------------------------------------------------------------------------*/

    QWidget *sign_in_widget = new QWidget();

    QLabel *first_name_label = new QLabel("First Name: ", this);
    QLineEdit *_insert_first_name = new QLineEdit(this);
    QHBoxLayout *first_name_layout = new QHBoxLayout();
    first_name_layout->addWidget(first_name_label);
    first_name_layout->addWidget(_insert_first_name);

    QLabel *last_name_label = new QLabel("Last Name: ", this);
    QLineEdit *_insert_last_name = new QLineEdit(this);
    QHBoxLayout *last_name_layout = new QHBoxLayout();
    last_name_layout->addWidget(last_name_label);
    last_name_layout->addWidget(_insert_last_name);

    QLabel *phone_number_label = new QLabel("Phone Number: ", this);
    QLineEdit *_insert_phone_number = new QLineEdit(this);
    QHBoxLayout *phone_number_layout = new QHBoxLayout();
    phone_number_layout->addWidget(phone_number_label);
    phone_number_layout->addWidget(_insert_phone_number);

    QLabel *password_label_2 = new QLabel("Password: ", this);
    QLineEdit *_insert_password = new QLineEdit(this);
    _insert_password->setEchoMode(QLineEdit::Password);
    QHBoxLayout *password_layout = new QHBoxLayout();
    password_layout->addWidget(password_label_2);
    password_layout->addWidget(_insert_password);

    QLabel *password_confirm_label = new QLabel("Confirm Password: ", this);
    QLineEdit *_insert_password_confirmation = new QLineEdit(this);
    _insert_password_confirmation->setEchoMode(QLineEdit::Password);
    QHBoxLayout *password_confirm_layout = new QHBoxLayout();
    password_confirm_layout->addWidget(password_confirm_label);
    password_confirm_layout->addWidget(_insert_password_confirmation);

    QLabel *secret_question_label = new QLabel("Secret Question: ", this);
    QLineEdit *_insert_secret_question = new QLineEdit(this);
    QHBoxLayout *secret_question_layout = new QHBoxLayout();
    secret_question_layout->addWidget(secret_question_label);
    secret_question_layout->addWidget(_insert_secret_question);

    QLabel *secret_answer_label = new QLabel("Secret Answer: ", this);
    QLineEdit *_insert_question_answer = new QLineEdit(this);
    QHBoxLayout *secret_answer_layout = new QHBoxLayout();
    secret_answer_layout->addWidget(secret_answer_label);
    secret_answer_layout->addWidget(_insert_question_answer);

    QPushButton *sign_in_button = new QPushButton("Sign In", this);
    connect(sign_in_button, &QPushButton::clicked, this, [=]() {});

    QVBoxLayout *sign_in_layout = new QVBoxLayout();
    sign_in_layout->addLayout(first_name_layout);
    sign_in_layout->addLayout(last_name_layout);
    sign_in_layout->addLayout(phone_number_layout);
    sign_in_layout->addLayout(password_layout);
    sign_in_layout->addLayout(password_confirm_layout);
    sign_in_layout->addLayout(secret_question_layout);
    sign_in_layout->addLayout(secret_answer_layout);
    sign_in_layout->addWidget(sign_in_button);

    QGroupBox *group_box_2 = new QGroupBox("Sign In System");
    group_box_2->setLayout(sign_in_layout);

    QGridLayout *sign_in_grid = new QGridLayout(sign_in_widget);
    sign_in_grid->addWidget(group_box_2, 0, 0, 1, 1, Qt::AlignCenter);

    /*-----------------------------------¬------------------------------------------------------------------------------------------------------------------------------------*/

    QWidget *chat_widget = new QWidget();

    QLabel *name = new QLabel("My Name: ", chat_widget);
    _name = new QLineEdit(chat_widget);
    _name->setPlaceholderText("INSERT YOUR NAME THEN PRESS ENTER");
    connect(_name, &QLineEdit::returnPressed, this, &client_main_window::on_name_changed);

    QHBoxLayout *hbox_2 = new QHBoxLayout();
    hbox_2->addWidget(name);
    hbox_2->addWidget(_name);

    _list = new QListWidget(chat_widget);
    _list->setSelectionMode(QAbstractItemView::SingleSelection);
    _list->setMinimumWidth(200);
    _list->setFont(QFont("Arial", 20));
    _list->setDisabled(true);
    _list->setItemDelegate(new separator_delegate(_list));
    connect(_list, &QListWidget::itemClicked, this, &client_main_window::on_item_clicked);

    QLabel *chats_label = new QLabel("CHATS", chat_widget);

    QVBoxLayout *VBOX_2 = new QVBoxLayout(chat_widget);
    VBOX_2->addLayout(hbox_2);
    VBOX_2->addWidget(chats_label);
    VBOX_2->addWidget(_list);

    /*-----------------------------------¬------------------------------------------------------------------------------------------------------------------------------------*/

    _stack->addWidget(login_widget);
    _stack->addWidget(sign_in_widget);
    _stack->addWidget(chat_widget);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/
void client_main_window::connected()
{
    _stack->setCurrentIndex(2);

    if (!_server_wid)
    {
        _server_wid = new client_chat_window(_db_connection, this);

        _list->addItem("Server");

        _server_wid->setObjectName("Server");
        _stack->addWidget(_server_wid);

        _window_map.insert("Server", _server_wid);
    }

    connect(_server_wid, &client_chat_window::client_connected, this, &client_main_window::on_client_connected);
    connect(_server_wid, &client_chat_window::clients_list, this, &client_main_window::on_clients_list);
    connect(_server_wid, &client_chat_window::client_name_changed, this, &client_main_window::on_client_name_changed);
    connect(_server_wid, &client_chat_window::client_disconnected, this, &client_main_window::on_client_disconnected);
    connect(_server_wid, &client_chat_window::text_message_received, this, &client_main_window::on_text_message_received);
    connect(_server_wid, &client_chat_window::swipe_right, this, &client_main_window::on_swipe_right);

    connect(_server_wid, &client_chat_window::is_typing_received, this, [=](QString sender)
            { _status_bar->showMessage(QString("%1 is typing...").arg(sender), 1000); });

    connect(_server_wid, &client_chat_window::socket_disconnected, this, [=]()
            { _stack->setDisabled(true); _status_bar->showMessage("SERVER DISCONNECTED YOU", 999999); });

    connect(_server_wid, &client_chat_window::text_message_sent, this, [=](QString client_name)
            { add_on_top(client_name); });

    _status_bar->showMessage("Connected to the Server", 1000);
}

void client_main_window::on_item_clicked(QListWidgetItem *item)
{
    QString client_name = item->text();

    QWidget *wid = _stack->findChild<QWidget *>(client_name);
    if (wid)
        _stack->setCurrentIndex(_stack->indexOf(wid));
    else
        qDebug() << "client_main_window--> on_item_clicked()--> window to forward not FOUND: " << client_name;
}

void client_main_window::on_name_changed()
{
    if (!_name->text().isEmpty())
    {
        _list->setEnabled(true);

        for (QWidget *win : _window_map)
        {
            client_chat_window *wid = qobject_cast<client_chat_window *>(win);
            wid->set_name(_name->text());
        }
    }
}

void client_main_window::on_client_connected(QString client_name)
{
    client_chat_window *wid = new client_chat_window(client_name, this);
    connect(wid, &client_chat_window::swipe_right, this, &client_main_window::on_swipe_right);

    wid->window_name(client_name);

    _list->addItem(client_name);

    wid->setObjectName(client_name);
    _stack->addWidget(wid);

    _name_list.insert(client_name, client_name);
    _window_map.insert(client_name, wid);
}

void client_main_window::on_clients_list(QString my_name, QHash<QString, QString> other_clients)
{
    for (QString client_name : other_clients.values())
    {
        if (client_name.compare(my_name))
        {
            client_chat_window *wid = new client_chat_window(other_clients.key(client_name), this);
            connect(wid, &client_chat_window::swipe_right, this, [=]()
                    { _stack->setCurrentIndex(2); });

            wid->window_name(client_name);

            _list->addItem(client_name);

            wid->setObjectName(client_name);
            _stack->addWidget(wid);

            _name_list.insert(other_clients.key(client_name), client_name);
            _window_map.insert(client_name, wid);
        }
    }
}

void client_main_window::on_client_disconnected(QString client_name)
{
    QWidget *win = _window_map.value(client_name);
    if (win)
    {
        QList<QListWidgetItem *> items = _list->findItems(client_name, Qt::MatchExactly);
        if (!items.isEmpty())
            delete items.first();

        _window_map.remove(client_name);
        _name_list.remove(client_name);
    }
    else
        qDebug() << "client_main_window ---> on_client_disconnected() --> client_name to Disconnect not FOUND: " << client_name;
}

void client_main_window::on_text_message_received(QString sender, QString message)
{
    QWidget *win = _window_map.value(sender);
    if (win)
    {
        client_chat_window *wid = qobject_cast<client_chat_window *>(win);
        if (wid)
        {
            wid->message_received(message);
            add_on_top(sender);
        }
        else
            qDebug() << "client_main_window ---> on_text_message_received() --> ERROR CASTING THE WIDGET:";
    }
    else
    {
        client_chat_window *wid = new client_chat_window(_name_list.key(sender), this);
        if (wid)
        {
            wid->message_received(message);
            add_on_top(sender);

            _list->addItem(sender);

            wid->setObjectName(sender);
            _stack->addWidget(wid);

            _window_map.insert(sender, wid);
        }
        else
            qDebug() << "client_main_window ---> on_text_message_received() --> Couldn't Create a new Conversation for the client :" << sender;
    }
}

void client_main_window::on_client_name_changed(QString old_name, QString client_name)
{
    QWidget *win = _window_map.value(old_name);
    if (win)
    {
        QWidget *wid = _stack->findChild<QWidget *>(old_name);
        wid->setObjectName(client_name);

        QList<QListWidgetItem *> items = _list->findItems(old_name, Qt::MatchExactly);
        if (!items.isEmpty())
        {
            QListWidgetItem *item_to_change = items.first();

            item_to_change->setText(client_name);
        }
        else
            qDebug() << "client_main_window ---> on_client_name_changed() ---> Client Name not Found in the _list: " << old_name;

        _window_map.remove(old_name);
        _window_map.insert(client_name, win);

        client_chat_window *wind = qobject_cast<client_chat_window *>(win);
        if (wind)
            wind->window_name(client_name);
        else
            qDebug() << "client_main_window ---> on_client_name_changed() ---> ERROR CASTING THE WIDGET:";

        _name_list.remove(old_name);
        _name_list.insert(old_name, client_name);
    }
    else
        qDebug() << "client_main_window ---> on_client_name_changed() ---> client_name to change not FOUND in the window_map:" << old_name;
}

/*-------------------------------------------------------------------- Functions --------------------------------------------------------------*/

void client_main_window::add_on_top(const QString &client_name)
{
    QList<QListWidgetItem *> items = _list->findItems(client_name, Qt::MatchExactly);
    if (!items.empty())
    {
        QListWidgetItem *item_to_replace = items.first();

        _list->takeItem(_list->row(item_to_replace));
        _list->insertItem(0, item_to_replace);
    }
    else
        _list->insertItem(0, client_name);
}

void client_main_window::mousePressEvent(QMouseEvent *event)
{
    drag_start_position = event->pos();
    dragging = true;
}

void client_main_window::mouseMoveEvent(QMouseEvent *event)
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
}

void client_main_window::on_swipe_right()
{
    if (_stack->currentIndex() > 2)
        _stack->setCurrentIndex(2);
    else
        _stack->setCurrentIndex(0);
}