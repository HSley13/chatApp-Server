#pragma once

#include "client_manager.h"
#include "chat_line.h"
#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>

class client_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    client_chat_window(QWidget *parent = nullptr);
    client_chat_window(QString destinator, QWidget *parent = nullptr);

    const QString &destinator() const;
    void window_name(QString name);

    QString my_name();
    void set_name(QString insert_name);

    void set_up_window();

    void message_received(QString message);

    QLabel *label;

private:
    QWidget *central_widget;

    QStatusBar *status_bar;

    static client_manager *_client;
    chat_line *wid;

    QListWidget *list;
    QListWidgetItem *line;

    QLineEdit *insert_message;

    QPushButton *send_button;
    QPushButton *send_file_button;

    QPushButton *file;
    QDir dir;

    static QString _my_name;
    static QString _insert_name;
    QString _destinator;

    QString _window_name;

    static chat_protocol *_protocol;

signals:
    void clients_list(QString my_name, QMap<QString, QString> other_clients);
    void client_connected(QString client_name);
    void client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name);

    void text_message_received(QString sender, QString message);
    void is_typing_received(QString sender);

    void socket_disconnected();

    void update_label(QLabel *label);

private slots:
    void
    send_message();
    void send_message_client();

    void send_is_typing();
    void send_is_typing_client();

    void send_file();
    void send_file_client();

    void file_saved(QString path);

    void folder();
    void folder_client();

    void on_text_message_received(QString sender, QString message);
    void on_is_typing_received(QString sender);

    void on_init_receiving_file(QString file_name, qint64 file_size);
    void on_init_receiving_file_client(QString sender, QString file_name, qint64 file_size);

    void on_reject_receiving_file();
    void on_reject_receiving_file_client(QString sender);

    void on_clients_list(QString my_name, QMap<QString, QString> other_clients);
    void on_client_connected(QString client_name);
    void on_client_name_changed(QString old_name, QString client_name);
    void on_client_disconnected(QString client_name);

    void on_socket_disconnected();

    void on_update_label(QLabel *label);

    void on_file_saved(QString path);
};