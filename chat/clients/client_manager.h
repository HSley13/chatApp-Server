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

    void send_text(QString sender, QString receiver, QString text);
    void send_name(QString name);
    void send_is_typing(QString sender, QString receiver);

    void send_init_sending_file(QString filename);
    void send_accept_file();
    void send_reject_file();

    void send_file();
    void save_file();

private:
    QWidget *_central_widget;

    static QTcpSocket *_socket;
    QHostAddress _ip;
    int _port;

    static chat_protocol *_protocol;

    QString _file_name;

signals:
    void text_message_received(QString sender, QString message);
    void is_typing_received(QString sender);

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void reject_receiving_file();

    void file_saved(QString path);

    void client_connected(QString client_name);
    void clients_list(QString my_name, QMap<QString, QString> other_clients);
    void client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name);

    void disconnected_from(QString client_name);

    void socket_disconnected();

private slots:
    void on_disconnected();

    void on_ready_read();
};