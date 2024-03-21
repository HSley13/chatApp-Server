#pragma once

#include "server_chat_window.h"
#include "server_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>

class server_main_window : public QMainWindow
{
    Q_OBJECT
public:
    server_main_window(QWidget *parent = nullptr);
    ~server_main_window();

private:
    QWidget *central_widget;
    QWidget *wid;

    QListWidget *list;
    QTabWidget *tabs;

    QPushButton *disconnect_all;

    server_manager *_server;
    server_chat_window *_chat;
    server_manager *_clients;

    QStatusBar *status_bar;

    QVBoxLayout *vbox;

signals:

private slots:
    void disconnect_all_clients();
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);

    void set_client_name(QString name);

    void is_typing_received(QString name);
};