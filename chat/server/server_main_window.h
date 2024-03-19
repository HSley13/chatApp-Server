#pragma once

#include "server_chat_window.h"
#include "server_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QStatusBar>

class server_main_window : public QMainWindow
{
    Q_OBJECT
public:
    server_main_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    QListWidget *list;
    QTabWidget *tabs;
    QPushButton *disconnect_all;

    server_manager *_server;
    server_chat_window *_chat;
    server_manager *_clients;

    QStatusBar *status_bar;

signals:

private slots:
    void disconnect_all_clients();
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void set_client_name(QString name);

    void is_typing_received(QString name);
};