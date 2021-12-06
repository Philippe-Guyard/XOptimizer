#include "interaction_service.h"
#include <parser/pbf-parser.h>

#include <iostream>
#include <fstream>
#include <QString>

#include <algorithm>
#include <memory>
#include <chrono>
#include <string>

namespace XOptimizer {
    InteractionService::InteractionService() {

    }

    InteractionService::~InteractionService() {

    }

    void InteractionService::download_and_parse_map(const std::string &region, const std::string &department) {
        qDebug() << "Download and parse started.";

        //TODO: This doesn't work
        //map_file_path = m_file_storage.get_save_path_from_map_name(region + "_" + department);
        map_file_path = QString::fromStdString("./" + region + "_" + department);
        auto reply = api_wrapper.download(region, department, map_file_path);
        QObject::connect(reply, &QNetworkReply::finished, [this]() {
            qDebug() << "Download finished.";
            this->parse_map();
            qDebug() << "Download exit.";
        });
        qDebug() << "Download and parse ended.";
    }

    void InteractionService::parse_map() {
        auto start = std::chrono::high_resolution_clock::now();
        std::shared_ptr<std::ifstream> map_stream = std::make_shared<std::ifstream>(map_file_path.toStdString());
        PBFParser::PBFParser parser(map_stream);

        map_file_ptr = parser.parse();
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }

    void InteractionService::read_csv(QFile* file) {
        file_to_order(file, orders);
    }

    OpenStreetMapWrapper* InteractionService::get_api_wrapper(){
        return &api_wrapper;
    }
}
