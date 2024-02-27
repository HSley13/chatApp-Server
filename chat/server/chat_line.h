#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class chat_line : public QMainWindow
{
    Q_OBJECT
public:
    chat_line(QWidget *parent = nullptr);
    void set_message(QString message, bool is_mine = false);

private:
    QWidget *central_widget;

    QVBoxLayout *VBOX;

    QLabel *message;
    QLabel *time;
};