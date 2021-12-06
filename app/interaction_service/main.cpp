#include "mainwindow.h"
#include "testing.h"
#include <QLoggingCategory>

#include <QApplication>

#define TESTING 1

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#if TESTING
    XOptimizer::InteractionService service;
    Testing test(&service);
    test.test_download();
//    test.run_all();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}

