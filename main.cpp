#include "mainwindow.h"
#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Server server;
    server.start();

    return a.exec();
}
