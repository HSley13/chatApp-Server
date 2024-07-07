#pragma once

#include "chat_protocol.h"
#include "server_manager.h"
#include "chat_line.h"
class server_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    server_chat_window(QWebSocket *client, QWidget *parent = nullptr);

    void disconnect_from_host();

    void add_file(const QString &path);

private:
    QListWidget *_list;

    QLineEdit *_insert_message;
    QPushButton *_send_button;

    server_manager *_client;
    chat_protocol *_protocol;

    QPushButton *_file;

    QDir dir;

signals:
    void client_name_changed(const QString &original_name, const QString &old_name, const QString &name);
    void is_typing_received(const QString &sender, const QString &receiver);

    void text_for_other_client(const QString &sender, const QString &receiver, const QString &message);
    void file_for_other_client(const QString &sender, const QString &receiver, const QString &file_name);

    void reject_receiving_file_for_other_clients(const QString &sender, const QString &receiver);

private slots:
    void on_client_name_changed(const QString &original_name, const QString &old_name, const QString &name);

    void send_message();

    void folder();

    void on_text_message_received(const QString &message, const QString &time);
};