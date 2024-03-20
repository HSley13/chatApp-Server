#pragma once

#include "client_manager.h"
#include <QMainWindow>
#include <QWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

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

    client_manager *_client;

    QListWidget *list;
    QLineEdit *insert_message;
    QLineEdit *insert_name;
    QPushButton *send_button;

signals:

private slots:
    void connection();

    void send_message();
    void send_name();
    void send_file();

    void text_message_received(QString message);
    void is_typing_received();

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void reject_receiving_file();

    void file_saved(QString path);

    void folder();
};