#pragma once

#include "chat_protocol.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QHostAddress>
#include <QMap>

#include <iostream>
#include <vector>
#include <mutex>

class port_pool
{
private:
    std::vector<int> ports;
    std::mutex mtx;

public:
    port_pool(int start, int end);

    int allocate_port();

    void deallocate_port(int port);

    void deallocate_all();
};

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

    QString name() const;

    QMap<QString, QTcpSocket *> _clients;

    static QMap<QString, QString> _names;

    friend class port_pool;

private:
    QWidget *central_widget;

    QTcpServer *_server;
    chat_protocol *_protocol;

    QTcpSocket *_socket;

    QString _file_name;

    QHostAddress _ip;
    int _port;

    static port_pool *_pool;

    void send_file();

    void save_file();

    void file_for_other_clients(QString sender, QString receiver, QString file_name);
    void reject_receiving_file_clients(QString sender, QString receiver);

signals:
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void text_message_received(QString sender, QString receiver, QString message);
    void client_name_changed(QString old_name, QString name);
    void is_typing_received(QString sender, QString receiver);

    void init_receiving_file(QString sender, QString file_name, qint64 file_size);
    void init_receiving_file_client(QString sender, QString receiver, QString file_name);

    void file_saved(QString path);

    void reject_receiving_file(QString sender);

private slots:
    void new_connection();
    void on_client_disconnected();

    void on_ready_read();

public slots:
    void on_text_for_other_clients(QString sender, QString receiver, QString message);
};
