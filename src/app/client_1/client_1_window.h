#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class client_1_window : public QMainWindow
{
    Q_OBJECT

public:
    client_1_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;

    QListWidget *list;

    QPushButton *send;

    QLineEdit *insert_message;

signals:
private slots:
};