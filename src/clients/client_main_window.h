#pragma once

#include "database.h"
#include "client_chat_window.h"

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class client_main_window : public QMainWindow
{
    Q_OBJECT
public:
    client_main_window(sql::Connection *db_connection, QWidget *parent = nullptr);

    void add_on_top(const QString &client_name);

    sql::Connection *_db_connection;

private:
    QStackedWidget *_stack;

    QStatusBar *_status_bar;

    QTabWidget *_tabs;

    QPoint drag_start_position;
    bool dragging = false;

    static client_chat_window *_server_wid;
    static QHash<QString, QWidget *> _window_map;
    static QHash<QString, int> _phone_list;

    QLineEdit *_name;
    QLineEdit *_user_phone_number;
    QLineEdit *_user_password;
    QLineEdit *_search_phone_number;

    QLineEdit *_insert_first_name;
    QLineEdit *_insert_last_name;
    QLineEdit *_insert_phone_number;
    QLineEdit *_insert_password;
    QLineEdit *_insert_password_confirmation;
    QLineEdit *_insert_secret_question;
    QLineEdit *_insert_secret_answer;

    QListWidget *_list;

    QComboBox *_friend_list;

    void
    mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void swipe_right();

private slots:
    void on_log_in();

    void on_client_name_changed(QString old_name, QString client_name);
    void on_client_disconnected(QString client_name);

    void on_text_message_received(QString sender, QString message);
    void on_name_changed();

    void on_item_clicked(QListWidgetItem *item);

    void on_swipe_right();

    void new_conversation(const QString &name);

    void on_sign_in();

    void on_client_added_you(QString name, QString ID, int conversation_ID);

    void on_friend_list(QHash<int, QHash<QString, int>> list);

    void on_lookup_friend_result(QString full_name, int conversation_ID);
};