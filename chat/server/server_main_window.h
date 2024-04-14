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
    static QMap<QString, QWidget *> window_map;

    QVBoxLayout *vbox;

private slots:
    void disconnect_all_clients();
    void on_new_client_connected(QTcpSocket *client);
    void on_new_client_disconnected(QTcpSocket *client);

    void on_client_name_changed(QString original_name, QString old_name, QString name);

    void on_is_typing_received(QString sender, QString receiver);

    void close_tabs(int index);
};