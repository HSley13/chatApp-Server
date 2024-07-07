#pragma once

#include "server_chat_window.h"
#include "server_manager.h"

class server_main_window : public QMainWindow
{
    Q_OBJECT
public:
    server_main_window(QSqlDatabase &db_connection, QWidget *parent = nullptr);
    ~server_main_window();

private:
    QSqlDatabase _db_connection;

    QListWidget *_list;
    QTabWidget *_tabs;

    QPushButton *_disconnect_all;

    static server_manager *_server;
    static chat_protocol *_protocol;

    QStatusBar *_status_bar;
    static QHash<QString, QWidget *> _window_map;

private slots:
    void on_new_client_connected(QWebSocket *client);
    void on_new_client_disconnected(QWebSocket *client);

    void on_client_name_changed(const QString &original_name, const QString &old_name, const QString &name);

    void on_is_typing_received(const QString &sender, const QString &receiver);

    void close_tabs(int index);
};