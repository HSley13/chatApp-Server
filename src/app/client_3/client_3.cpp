#include "client_3_window.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    client_3_window *Main_window = new client_3_window();
    Main_window->show();

    return app.exec();
}