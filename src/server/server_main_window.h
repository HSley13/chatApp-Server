#pragma once

#include "server_chat_window.h"
#include "server_manager.h"

#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class server_main_window : public QMainWindow
{
    Q_OBJECT
public:
    server_main_window(sql::Connection *db_connection, QWidget *parent = nullptr);
    ~server_main_window();

    sql::Connection *_db_connection;

private:
    QListWidget *_list;
    QTabWidget *_tabs;

    QPushButton *_disconnect_all;

    static server_manager *_server;
    static chat_protocol *_protocol;

    QStatusBar *_status_bar;
    static QHash<QString, QWidget *> _window_map;

private slots:
    void on_new_client_connected(QTcpSocket *client);
    void on_new_client_disconnected(QTcpSocket *client);

    void on_client_name_changed(QString original_name, QString old_name, QString name);

    void on_is_typing_received(QString sender, QString receiver);

    void close_tabs(int index);
};