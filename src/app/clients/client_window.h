#pragma once

#include "client_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class client_window : public QMainWindow
{
    Q_OBJECT

public:
    client_window(QWidget *parent = nullptr);

private: // variables
    QMenuBar *menu_bar;

    QMenu *menu;

    QAction *connection;
    QAction *exit;

    QWidget *central_widget;

    QListWidget *list;

    QPushButton *send;

    QLineEdit *insert_message;

    client_manager *_client;

private: // functions
signals:

private slots:
    void connection_func();
    void exit_func();
    void data_receive(QByteArray data);
    void send_func();
};