#include "client_1_window.h"
#include <QMainWindow>
#include <QWidget>

client_1_window::client_1_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
}