#include "chat_window.h"
#include <QApplication>
#include <QTcpSocket>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTcpSocket *client = new QTcpSocket(this);

    chat_window *Main_window = new chat_window(client);
    Main_window->show();

    return app.exec();
}