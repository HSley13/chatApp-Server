#pragma once

#include "chat_protocol.h"
#include "server_manager.h"
#include "chat_line.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>
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
    QWidget *central_widget;

    QListWidget *list;
    QListWidgetItem *line;

    QLineEdit *insert_message;
    QPushButton *send_button;

    server_manager *_client;
    chat_protocol *_protocol;
    chat_line *wid;

    QDir dir;

signals:
    void client_name_changed(QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void text_for_other_client(QString sender, QString receiver, QString message);

private slots:
    void send_message();

    void folder();
    void send_file();

    void on_text_message_received(QString sender, QString receiver, QString message);
    void on_is_typing_received(QString sender, QString receiver);

    void on_init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void on_file_saved(QString path);

    void on_client_name_changed(QString old_name, QString client_name);
};