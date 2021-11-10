#include "Interaction_service.h"
#include <Utils/Parser/pbf-parser.h>
#include <Utils/Parser/pbf-parser.cpp>
#include <Utils/Downloader/Downloader.cpp>

#include <QApplication>
namespace XOptimiser::interaction_service{
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interaction_service w;
    //w.show();
    return a.exec();
}
};
