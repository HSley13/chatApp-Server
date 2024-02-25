#include "client_3_window.h"
#include <QMainWindow>
#include <QWidget>

client_3_window::client_3_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
}