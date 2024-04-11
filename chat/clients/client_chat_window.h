#pragma once

#include "client_manager.h"
#include "chat_line.h"
#include "chat_protocol.h"
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

class client_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    client_chat_window(QWidget *parent = nullptr);
    client_chat_window(QString destinator, QWidget *parent = nullptr);

    void set_up_window();

    const QString &destinator() const;

    QString my_name();
    QString name_inserted();

    void message_received(QString message);

    void disconnect_client();

private:
    QWidget *central_widget;

    QStatusBar *status_bar;

    QMenuBar *menu_bar;
    QMenu *menu;

    static client_manager *_client;
    chat_line *wid;

    QListWidget *list;
    QListWidgetItem *line;

    QLineEdit *insert_message;
    QLineEdit *insert_name;

    QPushButton *send_button;

    QHBoxLayout *hbox;
    QVBoxLayout *VBOX;

    QString _my_name;
    QString _destinator;

    chat_protocol *_protocol;

    QString _primordial_name;

signals:
    void connection_ACK(QString my_name, QStringList other_clients);
    void client_connected(QString client_name);
    void client_name_changed(QString old_name, QString client_name);
    void client_disconnected(QString client_name, QString my_name);

    void text_message_received(QString sender, QString message);

    void disconnect_from(QString client_name);

    void is_typing_received(QString sender);

private slots:
    void send_message();
    void send_message_client();
    void send_name();
    void send_file();

    void on_is_typing_received(QString sender);

    void init_receiving_file(QString client_name, QString file_name, qint64 file_size);
    void reject_receiving_file();

    void file_saved(QString path);
    void folder();

    void on_connection_ACK(QString my_name, QStringList other_clients);
    void on_client_connected(QString client_name);
    void on_client_name_changed(QString old_name, QString client_name);
    void on_client_disconnected(QString client_name);

    void on_text_message_received(QString sender, QString message);

    void send_is_typing(QString receiver);
    void send_is_typing_client(QString receiver);
};