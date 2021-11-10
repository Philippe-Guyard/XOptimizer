#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H
#endif

//#include <utils/parser/pbf-parser.h>
//#include <utils/parser/pbf-parser.cpp>
#include <utils/downloader.cpp>
#include<string>

class InteractionService {
public:
    InteractionService();
    ~InteractionService();

    void download_and_parse_map(const std::string& region, const std::string& department);
private:
    QString map_file_path;
    Downloader downloader;
};




