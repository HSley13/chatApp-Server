#include "client_main_window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    client_main_window *Main_window = new client_main_window();
    Main_window->show();

    return app.exec();
}