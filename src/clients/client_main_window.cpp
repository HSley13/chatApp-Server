#include "client_main_window.h"

QHash<QString, QWidget *> client_main_window::_window_map = QHash<QString, QWidget *>();
QHash<QString, QString> client_main_window::_name_list = QHash<QString, QString>();

client_chat_window *client_main_window::_server_wid = nullptr;
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
    _user_phone_number = new QLineEdit(login_widget);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(id_label);
    hbox->addWidget(_user_phone_number);

    QLabel *password_label = new QLabel("Enter your Password: ", this);
    _user_password = new QLineEdit(this);

    QHBoxLayout *hbox_1 = new QHBoxLayout();
    hbox_1->addWidget(password_label);
    hbox_1->addWidget(_user_password);

    QPushButton *log_in = new QPushButton("Log In", login_widget);
    connect(log_in, &QPushButton::clicked, this, &client_main_window::on_log_in);

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
    _insert_first_name = new QLineEdit(this);
    QHBoxLayout *first_name_layout = new QHBoxLayout();
    first_name_layout->addWidget(first_name_label);
    first_name_layout->addWidget(_insert_first_name);

    QLabel *last_name_label = new QLabel("Last Name: ", this);
    _insert_last_name = new QLineEdit(this);
    QHBoxLayout *last_name_layout = new QHBoxLayout();
    last_name_layout->addWidget(last_name_label);
    last_name_layout->addWidget(_insert_last_name);

    QLabel *phone_number_label = new QLabel("Phone Number: ", this);
    _insert_phone_number = new QLineEdit(this);
    QHBoxLayout *phone_number_layout = new QHBoxLayout();
    phone_number_layout->addWidget(phone_number_label);
    phone_number_layout->addWidget(_insert_phone_number);

    QLabel *password_label_2 = new QLabel("Password: ", this);
    _insert_password = new QLineEdit(this);
    _insert_password->setEchoMode(QLineEdit::Password);
    QHBoxLayout *password_layout = new QHBoxLayout();
    password_layout->addWidget(password_label_2);
    password_layout->addWidget(_insert_password);

    QLabel *password_confirm_label = new QLabel("Confirm Password: ", this);
    _insert_password_confirmation = new QLineEdit(this);
    _insert_password_confirmation->setEchoMode(QLineEdit::Password);
    QHBoxLayout *password_confirm_layout = new QHBoxLayout();
    password_confirm_layout->addWidget(password_confirm_label);
    password_confirm_layout->addWidget(_insert_password_confirmation);

    QLabel *secret_question_label = new QLabel("Secret Question: ", this);
    _insert_secret_question = new QLineEdit(this);
    QHBoxLayout *secret_question_layout = new QHBoxLayout();
    secret_question_layout->addWidget(secret_question_label);
    secret_question_layout->addWidget(_insert_secret_question);

    QLabel *secret_answer_label = new QLabel("Secret Answer: ", this);
    _insert_secret_answer = new QLineEdit(this);
    QHBoxLayout *secret_answer_layout = new QHBoxLayout();
    secret_answer_layout->addWidget(secret_answer_label);
    secret_answer_layout->addWidget(_insert_secret_answer);

    QPushButton *sign_in_button = new QPushButton("Sign In", this);
    connect(sign_in_button, &QPushButton::clicked, this, &client_main_window::on_sign_in);

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

    QLabel *fr_list = new QLabel("Start New conversation", this);
    _friend_list = new QComboBox(this);
    connect(_friend_list, &QComboBox::activated, this, &client_main_window::new_conversation);

    QHBoxLayout *hbox_3 = new QHBoxLayout();
    hbox_3->addWidget(fr_list);
    hbox_3->addWidget(_friend_list);

    _search_phone_number = new QLineEdit(this);
    _search_phone_number->setPlaceholderText("ADD PEOPLE VIA PHONE NUMBER, THEN PRESS ENTER");
    connect(_search_phone_number, &QLineEdit::returnPressed, this, &client_main_window::on_search_friend);

    QVBoxLayout *VBOX_2 = new QVBoxLayout(chat_widget);
    VBOX_2->addLayout(hbox_2);
    VBOX_2->addLayout(hbox_3);
    VBOX_2->addWidget(chats_label);
    VBOX_2->addWidget(_list);
    VBOX_2->addWidget(_search_phone_number);

    /*-----------------------------------¬------------------------------------------------------------------------------------------------------------------------------------*/

    _stack->addWidget(login_widget);
    _stack->addWidget(sign_in_widget);
    _stack->addWidget(chat_widget);
}

/*-------------------------------------------------------------------- Slots --------------------------------------------------------------*/

void client_main_window::on_sign_in()
{
    if (_insert_phone_number->text().toInt() == 0)
    {
        _insert_phone_number->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "Incorrect", "Enter a Valid Phone Number");

        return;
    }

    _insert_phone_number->setStyleSheet("border: 1px solid gray;");
    if (_insert_password->text().isEmpty())
    {
        _insert_password->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "Incorrect", "Password left Empty!!!!");

        return;
    }

    _insert_password->setStyleSheet("border: 1px solid gray;");

    if (_insert_password->text().compare(_insert_password_confirmation->text()))
    {
        _insert_password_confirmation->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "Incorrect", "Password Confirmation Incorrect");

        return;
    }

    _insert_password_confirmation->setStyleSheet("border: 1px solid gray;");

    if (_insert_secret_question->text().isEmpty())
    {
        _insert_secret_question->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "void!!!", "Secret Question left empty!!!");

        return;
    }

    _insert_secret_question->setStyleSheet("border: 1px solid gray;");

    if (_insert_secret_answer->text().isEmpty())
    {
        _insert_secret_question->setStyleSheet("border: 1px solid red;");
        QMessageBox::warning(this, "void!!!", "Answer left empty!!!");

        return;
    }

    _insert_secret_question->setStyleSheet("border: 1px solid gray;");

    QString info = "First Name : " + _insert_first_name->text() + "\n"
                                                                  "Last Name : " +
                   _insert_last_name->text() + "\n"
                                               " Phone Number : " +
                   _insert_phone_number->text() + "\n"
                                                  "Secret Question : " +
                   _insert_secret_question->text() + "\n"
                                                     "Secret Answer : " +
                   _insert_secret_answer->text() + "\n";
    bool OK;

    QMessageBox review;
    review.setWindowTitle("Information Review");
    review.setText(info);
    review.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int result = review.exec();

    if (result == QMessageBox::Cancel)
        return;

    std::string hash_password = Security::hashing_password(_insert_password->text().toStdString());

    Account::create_account(_db_connection, _insert_phone_number->text().toInt(), _insert_first_name->text().toStdString(), _insert_last_name->text().toStdString(), _insert_secret_question->text().toStdString(), _insert_secret_answer->text().toStdString(), hash_password);

    QMessageBox::information(this, "New Account", "Account Created Successfully");

    _insert_phone_number->clear();
    _insert_first_name->clear();
    _insert_last_name->clear();
    _insert_password->clear();
    _insert_password_confirmation->clear();
    _insert_secret_question->clear();
    _insert_secret_answer->clear();
}

void client_main_window::on_log_in()
{
    std::string hashed_password = Security::retrieve_hashed_password(_db_connection, _user_phone_number->text().toInt());

    if (hashed_password == "")
    {
        _user_phone_number->setStyleSheet("border: 1px solid red");

        return;
    }

    _user_phone_number->setStyleSheet("border: 1px solid gray");

    if (!Security::verifying_password(_user_password->text().toStdString(), hashed_password))
    {
        _user_password->setStyleSheet("border: 1px solid red");

        QMessageBox::warning(nullptr, "!!!", "Password Incorrect");

        return;
    }

    _user_password->setStyleSheet("border: 1px solid gray");

    _stack->setCurrentIndex(2);

    if (!_server_wid)
    {
        _server_wid = new client_chat_window(_db_connection, this);

        _list->addItem("Server");

        _server_wid->setObjectName("Server");
        _stack->addWidget(_server_wid);

        _window_map.insert("Server", _server_wid);

        _status_bar->showMessage("Connected to the Server", 1000);
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

    _user_phone_number->clear();
    _user_password->clear();
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
    connect(wid, &client_chat_window::text_message_sent, this, [=](QString client_name)
            { add_on_top(client_name); });

    wid->window_name(client_name);

    wid->setObjectName(client_name);
    _stack->addWidget(wid);

    _list->addItem(client_name);

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
            connect(wid, &client_chat_window::swipe_right, this, &client_main_window::on_swipe_right);
            connect(wid, &client_chat_window::text_message_sent, this, [=](QString client_name)
                    { add_on_top(client_name); });

            wid->window_name(client_name);

            wid->setObjectName(client_name);
            _stack->addWidget(wid);

            _list->addItem(client_name);

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

void client_main_window::on_text_message_received(QString sender, QString review)
{
    QWidget *win = _window_map.value(sender);
    if (win)
    {
        client_chat_window *wid = qobject_cast<client_chat_window *>(win);
        if (wid)
        {
            wid->message_received(review);
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
            wid->message_received(review);
            add_on_top(sender);

            wid->setObjectName(sender);
            _stack->addWidget(wid);

            _list->addItem(sender);

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

void client_main_window::on_swipe_right()
{
    if (_stack->currentIndex() > 2)
        _stack->setCurrentIndex(2);
    else
        _stack->setCurrentIndex(0);
}

void client_main_window::on_search_friend()
{
    /*
        Send request to the server to check if the client phone_number exist in the database
        ? (phone_number) add the client_name to the _friend_list along with its specifier : display a QMessageBox saying the phone_number wasn't found
    */
}

void client_main_window::new_conversation(int index)
{
    /*
        QString client_name = _friend_list->itemText(index);
        Open a client_chat_window() widget with the client_name
        Add the client_name in the _list if it isn't there.
    */
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
