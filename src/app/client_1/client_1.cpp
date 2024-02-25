#include "client_1_window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    client_1_window *Main_window = new client_1_window();
    Main_window->show();

    return app.exec();
}