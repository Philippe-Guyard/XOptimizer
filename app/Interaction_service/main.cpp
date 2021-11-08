#include "Interaction_service.h"
#include <Utils/Parser/pbf-parser.h>
#include <Utils/Parser/pbf-parser.cpp>
#include <Utils/Downloader/Downloader.cpp>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interaction_service w;
    w.show();
    return a.exec();
}
