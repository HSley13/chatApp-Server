#include "server_window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    server_window *Main_window = new server_window();
    Main_window->show();

    return app.exec();
}