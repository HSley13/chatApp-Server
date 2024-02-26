#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class client_chat : public QMainWindow
{
    Q_OBJECT

public:
    client_chat(QWidget *parent = nullptr);
    void set_message(QString message, bool is_my_message = false);

private:
    QWidget *central_widget;

    QVBoxLayout *VBOX;

    QLabel *_message;
    QLabel *_time;

private slots:
};