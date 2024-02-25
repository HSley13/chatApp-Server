#include "client_1_window.h"
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

client_1_window::client_1_window(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    resize(400, 400);

    list = new QListWidget(this);

    QLabel *message = new QLabel("Insert Message", this);
    insert_message = new QLineEdit(this);
    QHBoxLayout *hbox_1 = new QHBoxLayout(this);
    hbox_1->addWidget(message);
    hbox_1->addWidget(insert_message);

    send = new QPushButton("Send", this);

    QVBoxLayout *VBOX = new QVBoxLayout(this);
    VBOX->addWidget(list);
    VBOX->addLayout(hbox_1);
    VBOX->addWidget(send);

    central_widget->setLayout(VBOX);
}