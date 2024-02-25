#pragma once

#include "server_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTcpSocket>

class server_window : public QMainWindow
{
    Q_OBJECT

public:
    server_window(QWidget *parent = nullptr);

private: // variables
    QWidget *central_widget;
    QTabWidget *tabs;
    QListWidget *list;

    QPushButton *disconnet_all;
    QPushButton *send;

    QLineEdit *message_1;
    QLineEdit *message_2;
    QLineEdit *message_3;

    server_manager *_server;

private: // functions
    void setup_server();

signals:
private slots:
    void disconnet_all_function();
    void new_client_connected(QTcpSocket *client);
    void client_disconnected(QTcpSocket *client);
};