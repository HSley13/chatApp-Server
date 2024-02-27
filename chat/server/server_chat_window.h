#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class server_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    server_chat_window(QTcpSocket *client, QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    QListWidget *list;
    QLineEdit *insert_message;
    QPushButton *send_button;

    QTcpSocket *_socket;

signals:

private slots:
    void send_message();
    void data_receive();
    void disconnecton();
};