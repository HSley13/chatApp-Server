#pragma once

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
    void send_message(QString message);

private:
    QWidget *_central_widget;

    QTcpSocket *_socket;
    QHostAddress _ip;
    int _port;

signals:
    void connected();
    void disconnected();
    void data_receive(QByteArray message);

private slots:
    void ready_read();
};