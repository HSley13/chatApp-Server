#include "server_main_window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    server_main_window *Main_window = new server_main_window();
    Main_window->show();

    return app.exec();
}