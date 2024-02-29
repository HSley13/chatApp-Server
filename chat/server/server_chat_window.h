#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>

class server_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    server_chat_window(QTcpSocket *client, QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    static QListWidget *list;
    QLineEdit *insert_message;
    QPushButton *send_button;

    QTcpSocket *_socket;

    chat_protocol *_protocol;

    static void text_message(QString message);
    static void is_typing();
    // static void set_name(QString message);

    static QStatusBar *status_bar;

private slots:
    void send_message();
    void data_receive();
    void disconnecton();

    void send_is_typing();
};