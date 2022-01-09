#pragma once

#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H
#endif

#include <optional>
#include <parser/pbf-parser.h>
#include <utils/order_parser.h>
#include <utils/api_wrapper.h>
#include "file_storage.h"
#include <string>
#include <future>

namespace XOptimizer {
    class InteractionService {
    public:
        InteractionService();
        ~InteractionService();

        void download_and_parse_map(const std::string& region, const std::string& department, std::optional<std::function<void(qint64, qint64)>> download_callback = {});
        bool optimize_csv(QFile* file);
        void read_csv_as_table(QFile* file, QVector<QVector<QString>>& output);
        bool get_optimized_orders(QVector<QVector<QString>>& output_table, QVector<std::pair<double, double>>& path);
        OpenStreetMapWrapper* get_api_wrapper();
    private:
        void start_parsing_thread();
        void start_optimization_thread();

        QVector<Order> orders, optimized_orders;
        QString map_file_path;
        OpenStreetMapWrapper api_wrapper;
        std::shared_ptr<PBFParser::PBFFile> map_file_ptr;
        std::shared_ptr<Map> map;
        std::unique_ptr<FileStorage> m_file_storage;

        std::future<void> parsing_thread, optimization_thread;
    };
};




