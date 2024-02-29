#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

class client_manager : public QMainWindow
{
    Q_OBJECT
public:
    client_manager(QHostAddress ip = QHostAddress::LocalHost, int port = 12345, QWidget *parent = nullptr);
    void connect_to_server();
    void send_text(QString text);
    void send_name(QString name);
    void send_is_typing();

private:
    QWidget *_central_widget;

    QTcpSocket *_socket;
    QHostAddress _ip;
    int _port;

    chat_protocol *_protocol;

signals:
    void connected();
    void disconnected();

    void text_message_received(QString message);
    void is_typing_received();

private slots:
    void ready_read();
};