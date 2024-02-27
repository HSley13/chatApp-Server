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
    void set_message(QString message, bool is_mine = false);

private:
    QWidget *central_widget;

    QVBoxLayout *VBOX;

    QLabel *message;
    QLabel *time;
};