#include "client_2_window.h"
#include <QMainWindow>
#include <QWidget>

client_2_window::client_2_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
}