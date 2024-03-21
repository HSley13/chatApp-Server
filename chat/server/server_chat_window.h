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
    ~server_chat_window();

private:
    QWidget *central_widget;

    QListWidget *list;
    QListWidgetItem *line;

    QHBoxLayout *hbox;

    QLineEdit *insert_message;
    QPushButton *send_button;

    server_manager *_client;
    chat_protocol *_protocol;
    chat_line *wid;

    QDir dir;

signals:
    void client_name_changed(QString name);
    void is_typing(QString name);

private slots:
    void send_message();
    void disconnection();

    void text_message_received(QString message);
    void is_typing_received();

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void file_saved(QString path);

    void folder();
    void send_file();

    void on_client_name_changed(QString);
};