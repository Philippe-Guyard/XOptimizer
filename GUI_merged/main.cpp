#include "xoptimizer.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XOptimizer w;
    w.show();
    return a.exec();

}

