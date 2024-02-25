#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>

class chat_window : public QMainWindow
{
    Q_OBJECT

public:
    chat_window(QTcpSocket *client, QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    QListWidget *list;

    QPushButton *send;

    QLineEdit *insert_message;

    QTcpSocket *_client;

signals:
private slots:
    void data_receive();
    void send_func();

    void client_disconnected();
};