#include "chat_line.h"
#include <QTime>

chat_line::chat_line(QWidget *parent)
    : QMainWindow(parent)
{
    central_widget = new QWidget();
    setCentralWidget(central_widget);

    VBOX = new QVBoxLayout(central_widget);
}

void chat_line::set_message(QString message, bool is_mine)
{
    QLabel *msg_label = new QLabel(message, this);
    QLabel *time_label = new QLabel(QTime::currentTime().toString(), this);

    QVBoxLayout *message_layout = new QVBoxLayout();

    if (is_mine)
    {
        msg_label->setAlignment(Qt::AlignRight);
        time_label->setAlignment(Qt::AlignRight);

        message_layout->addWidget(msg_label);
        message_layout->addWidget(time_label);
    }
    else
    {
        msg_label->setAlignment(Qt::AlignLeft);
        time_label->setAlignment(Qt::AlignLeft);

        message_layout->addWidget(msg_label);
        message_layout->addWidget(time_label);
    }

    VBOX->addLayout(message_layout);
}