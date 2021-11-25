#include "mainwindow.h"

#include <QApplication>

#include "testing.cpp"

int main(int argc, char *argv[])
{
    test_download();
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
