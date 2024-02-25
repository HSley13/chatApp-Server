#pragma once

#include <QMainWindow>
#include <QWidget>

class client_3_window : public QMainWindow
{
    Q_OBJECT

public:
    client_3_window(QWidget *parent = nullptr);

private:
    QWidget *central_widget;
signals:
private slots:
};