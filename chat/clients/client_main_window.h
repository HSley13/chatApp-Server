#pragma once

#include "client_manager.h"
#include "client_chat_window.h"
#include "client_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QMap>

class client_main_window : public QMainWindow
{
    Q_OBJECT
public:
    client_main_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    QStatusBar *status_bar;

    QMenuBar *menu_bar;
    QMenu *menu;

    QTabWidget *tabs;

    QVBoxLayout *VBOX;
    client_manager *_client;

    QMap<QString, QWidget *> window_map;

private slots:
    void connection();

    void on_connection_ACK(QString my_name, QStringList other_clients);
    void on_client_connected(QString client_name);
    void on_client_name_changed(QString old_name, QString client_name);
    void on_client_disconnected(QString client_name, QString my_name);
    void on_text_message_received(QString sender, QString message);

    void on_is_typing_received(QString sender);

    void close_tabs(int index);
};