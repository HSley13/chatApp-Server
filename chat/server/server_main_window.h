#pragma once

#include "server_chat_window.h"
#include "server_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QPushButton>

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

signals:

private slots:
    void disconnect_all_clients();
    void new_client_connected(QTcpSocket *client);
    void new_client_disconnected(QTcpSocket *client);
};