#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class client_chat_window : public QMainWindow
{
    Q_OBJECT
public:
    client_chat_window(QWidget *parent = nullptr);
    ~client_chat_window();

    void set_message(QString message, bool is_mine = false);

private:
    QWidget *central_widget;

    QVBoxLayout *VBOX;
    QVBoxLayout *message_layout;

    QLabel *message;
    QLabel *time;
};