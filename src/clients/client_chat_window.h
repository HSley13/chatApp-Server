#pragma once

#include "client_manager.h"
#include "chat_line.h"

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class client_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    client_chat_window(QString my_ID, QWidget *parent = nullptr);
    client_chat_window(QString destinator, QString name, int conversation_ID, QWidget *parent = nullptr);

    void window_name(QString name);

    QString my_name();
    void set_name(QString insert_name);

    void set_up_window();

    void message_received(QString message);

    void add_file(QString path, bool is_mine = true);

    void add_friend(QString ID);

    void retrieve_conversation(std::vector<std::string> messages);

private:
    QStatusBar *_status_bar;

    static client_manager *_client;

    QPushButton *_button_file;
    QListWidget *_list;

    QLineEdit *_insert_message;

    QPushButton *_send_file_button;

    QString _destinator_name;
    int _conversation_ID;

    QDir dir;
    QString _my_ID;

    static QString _my_name;
    static QString _insert_name;

    QString _destinator = "Server";
    QString _window_name = "Server";

    QPoint drag_start_position;
    bool dragging = false;

    std::vector<int> _conversation_list;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name);

    void text_message_received(QString sender, QString message);
    void is_typing_received(QString sender);

    void socket_disconnected();

    void update_button_file();

    void data_received_sent(QString client_name);

    void swipe_right();

    void client_added_you(QString name, QString ID, int conversation_ID);

    void lookup_friend_result(QString name, int conversation_ID);

    void friend_list(QHash<int, QHash<QString, int>> list);

private slots:
    void send_message();

    void send_file();
    void send_file_client();

    void folder();

    void on_init_receiving_file(QString file_name, qint64 file_size);
    void on_init_receiving_file_client(QString sender, QString ID, QString file_name, qint64 file_size);

    void on_file_saved(QString path);

    void start_recording();
};