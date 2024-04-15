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
#include <QLineEdit>
#include <QStackedWidget>
#include <QListWidget>

class client_main_window : public QMainWindow
{
    Q_OBJECT
public:
    client_main_window(QWidget *parent = nullptr);

    void add_on_top(const QString &client_name);

private:
    QStatusBar *_status_bar;

    QTabWidget *_tabs;

    client_manager *_client;

    static QMap<QString, QWidget *> _window_map;
    static QMap<QString, QString> _name_list;

    QLineEdit *_name;

    static QStackedWidget *_stack;
    QListWidget *_list;

    QPushButton *_back_button;

private slots:
    void connected();

    void on_clients_list(QString my_name, QMap<QString, QString> other_clients);
    void on_client_connected(QString client_name);
    void on_client_name_changed(QString old_name, QString client_name);
    void on_client_disconnected(QString client_name);

    void on_text_message_received(QString sender, QString message);
    void on_is_typing_received(QString sender);
    void on_name_changed();

    void on_item_clicked(QListWidgetItem *item);
};