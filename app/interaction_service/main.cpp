#include "mainwindow.h"
#include "testing.h"
#include <QLoggingCategory>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
		XOptimizer::InteractionService service;
		Testing test(&service);
		test.run_all();
//    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
//    MainWindow w;
//    w.show();

    return a.exec();
}

