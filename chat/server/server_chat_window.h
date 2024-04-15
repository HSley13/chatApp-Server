#pragma once

#include "chat_protocol.h"
#include "server_manager.h"
#include "chat_line.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QDir>

class server_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    server_chat_window(QTcpSocket *client, QWidget *parent = nullptr);

    void disconnect_from_host();

private:
    QListWidget *_list;

    QLineEdit *_insert_message;
    QPushButton *_send_button;

    server_manager *_client;
    chat_protocol *_protocol;

    QDir dir;

signals:
    void client_name_changed(QString original_name, QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void text_for_other_client(QString sender, QString receiver, QString message);

    void file_for_other_client(QString sender, QString receiver, QString file_name);

    void reject_receiving_file_for_other_clients(QString sender, QString receiver);

private slots:
    void send_message();

    void folder();
    void send_file();

    void on_text_message_received(QString sender, QString receiver, QString message);

    void on_init_receiving_file(QString sender, QString file_name, qint64 file_size);

    void on_file_saved(QString path);

    void on_client_name_changed(QString original_name, QString old_name, QString name);
};