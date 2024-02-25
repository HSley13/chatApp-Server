#pragma once

#include <QMainWindow>
#include <QWidget>

class client_2_window : public QMainWindow
{
    Q_OBJECT

public:
    client_2_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;
signals:
private slots:
};