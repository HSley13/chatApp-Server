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

    void send_init_sending_file(QString filename);
    void send_accept_file();
    void send_reject_file();

    void send_file();
    void save_file();

private:
    QWidget *_central_widget;

    QTcpSocket *_socket;
    QHostAddress _ip;
    int _port;

    chat_protocol *_protocol;

    QString _file_name;

signals:
    void connected();
    void disconnected();

    void text_message_received(QString message);
    void is_typing_received();

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void reject_receiving_file();

    void file_saved(QString path);

private slots:
    void ready_read();
};