#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H
#endif

#include <optional>
#include <parser/pbf-parser.h>
#include <utils/order_parser.h>
#include <utils/api_wrapper.h>
#include "file_storage.h"
#include <string>
#pragma once

namespace XOptimizer {
    class InteractionService {
    public:
        InteractionService();
        ~InteractionService();

        void download_and_parse_map(const std::string& region, const std::string& department, std::optional<std::function<void(qint64, qint64)>> download_callback = {});
        void read_csv(QFile* file);
        void parse_map();
        OpenStreetMapWrapper* get_api_wrapper();
        QVector<Order> orders;
    private:
        QString map_file_path;
        OpenStreetMapWrapper api_wrapper;
        std::shared_ptr<PBFParser::PBFFile> map_file_ptr;
        std::unique_ptr<FileStorage> m_file_storage;
    };
};




