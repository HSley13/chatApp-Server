#include "client_chat.h"
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDateTime>

client_chat::client_chat(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    VBOX = new QVBoxLayout();

    central_widget->setLayout(VBOX);
}

void client_chat::set_message(QString message, bool is_my_message)
{
    QLabel *message_label = new QLabel(message, this);
    QLabel *time_label = new QLabel(QDateTime::currentDateTime().toString("HH:mm"), this);

    QVBoxLayout *message_layout = new QVBoxLayout();

    if (is_my_message)
    {
        message_label->setAlignment(Qt::AlignRight);
        time_label->setAlignment(Qt::AlignRight);

        message_layout->addWidget(message_label);
        message_layout->addWidget(time_label);
    }
    else
    {
        message_layout->addWidget(message_label);
        message_layout->addWidget(time_label);
    }

    VBOX->addLayout(message_layout);
}