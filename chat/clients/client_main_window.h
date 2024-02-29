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

    client_manager *con;

    QListWidget *list;
    QLineEdit *insert_message;
    QLineEdit *insert_name;
    QPushButton *send_button;

signals:

private slots:
    void connection();
    void send_message();
    void data_text_receive(QString message);
    void send_name();

    void set_is_typing();
};