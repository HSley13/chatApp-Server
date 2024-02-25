#pragma once

#include <QMainWindow>
#include <QWidget>

class server_window : public QMainWindow
{
    Q_OBJECT

public:
    server_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;
signals:
private slots:
};