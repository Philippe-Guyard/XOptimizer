#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H
#endif

#include <parser/pbf-parser.h>
#include <utils/downloader.cpp>
#include <utils/order_parser.h>
#include <string>
#pragma once

namespace XOptimizer {
    class InteractionService {
    public:
        InteractionService();
        ~InteractionService();

        void download_and_parse_map(const std::string& region, const std::string& department);
        void read_csv(QFile* file);
    private:
        void parse_map();

        QString map_file_path;
        Downloader downloader;
        QVector<Order> orders;
        std::shared_ptr<PBFParser::PBFFile> map_file_ptr;
    };
};




