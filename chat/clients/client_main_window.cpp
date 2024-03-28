#include "client_main_window.h"
#include <QAction>
#include <QLabel>

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>

client_main_window::client_main_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    status_bar = new QStatusBar(this);
    setStatusBar(status_bar);

    menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);

    menu = new QMenu("OPTIONS", this);

    QAction *connection = new QAction("Connect", this);
    connect(connection, &QAction::triggered, this, &client_main_window::connection);

    menu->addAction(connection);
    menu_bar->addMenu(menu);

    tabs = new QTabWidget(this);
    tabs->setEnabled(false);

    VBOX = new QVBoxLayout(central_widget);
    VBOX->addWidget(tabs);
}

client_main_window::~client_main_window()
{
    delete central_widget;
}

void client_main_window::connection()
{
    client_chat_window *wid = new client_chat_window(this);
    tabs->addTab(wid, "Server");

    tabs->setEnabled(true);

    status_bar->showMessage("Connected to the Server", 1000);
}
