#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QtNetwork>
#include <QList>
#include <QMap>

#include <iostream>
#include <vector>
#include <mutex>

class server_manager : public QMainWindow
{
    Q_OBJECT
public:
    server_manager(QHostAddress ip = QHostAddress::LocalHost, int port = 12345, QWidget *parent = nullptr);
    server_manager(QTcpSocket *client, QWidget *parent = nullptr);

    void disconnect_from_host();
    void disconnect_all_clients();

    void is_typing_for_other_clients(QString sender, QString receiver);

    void send_text(QString text);
    void send_is_typing(QString sender);

    void send_init_sending_file(QString filename);
    void send_accept_file();
    void send_reject_file();

    void send_accept_file_client(QString receiver, int port);
    void send_reject_file_client(QString sender, QString receiver);

    void notify_other_clients(QString old_name, QString client_name);

    void send_file();
    void save_file();

    void file_for_other_clients(QString sender, QString receiver, QString file_name, qint64 file_size);
    void reject_receiving_file_clients(QString sender, QString receiver);

    QString name() const;

    static QMap<QString, QTcpSocket *> _clients;
    static QMap<QString, QString> _names;

    static void range(int start, int end);

    static int allocate_port();

    static void deallocate_all();

private:
    QWidget *central_widget;

    QTcpServer *_server;
    chat_protocol *_protocol;

    QTcpSocket *_socket;

    QString _file_name;

    QHostAddress _ip;
    int _port;

    static std::vector<int> _ports;

signals:
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void text_message_received(QString sender, QString receiver, QString message);
    void client_name_changed(QString original_name, QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void init_receiving_file(QString sender, QString file_name, qint64 file_size);
    void init_receiving_file_client(QString sender, QString receiver, QString file_name);

    void file_saved(QString path);

    void reject_receiving_file(QString sender);

private slots:
    void on_new_connection();
    void on_client_disconnected();

    void on_ready_read();

public slots:
    void on_text_for_other_clients(QString sender, QString receiver, QString message);
};
