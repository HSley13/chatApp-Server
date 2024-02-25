#include "server_window.h"
#include <QMainWindow>
#include <QWidget>

server_window::server_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);
}