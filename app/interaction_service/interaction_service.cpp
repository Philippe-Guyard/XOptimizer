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
        m_file_storage = std::make_unique<FileStorage>();
    }

    InteractionService::~InteractionService() {

    }

    void InteractionService::download_and_parse_map(const std::string &region, const std::string &department, std::optional<std::function<void(qint64, qint64)>> download_callback) {
        qDebug() << "Download and parse started.";

        map_file_path = m_file_storage->get_save_path_from_map_name(QString::fromStdString(region), QString::fromStdString(department));
        auto reply = api_wrapper.download(region, department, map_file_path);
        QObject::connect(reply, &QNetworkReply::finished, [this]() {
            qDebug() << "Download finished.";
            this->parse_map();
            qDebug() << "Download exit.";
        });
        if (download_callback.has_value()) {
            QObject::connect(reply, &QNetworkReply::downloadProgress, download_callback.value());
        }
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

    void InteractionService::optimize_csv(QFile* file) {
        QString new_path = m_file_storage->get_save_path_from_csv(file->fileName());
        QFile new_file(new_path);
        if (!new_file.open(QIODevice::ReadWrite)) {
            //TODO: Handle unknown error
            return;
        }

        //api_wrapper.searchCSV(file, &new_file);

        file_to_order(file, orders);
    }

    void InteractionService::read_csv_as_table(QFile *file, QVector<QVector<QString>> &output) {
        QVector<Order> temp_orders;
        file_to_order(file, temp_orders);
        if (temp_orders.size() == 0)
            return;
        //lat long adress id
        output = QVector<QVector<QString>>(temp_orders.size() + 1, QVector<QString>(4 + temp_orders[0].other_dict.size()));
        output[0][0] = "id";
        output[0][1] = "adresse";
        output[0][2] = "latitude";
        output[0][3] = "longitude";
        int j = 4;
        for(auto it : temp_orders[0].other_dict) {
            output[0][j++] = it;
        }
        for(int i = 0; i < temp_orders.size(); ++i) {
            output[i + 1][0] = QString::number(temp_orders[i].id);
            output[i + 1][1] = temp_orders[i].location;
            output[i + 1][2] = QString::number(temp_orders[i].geolocation.first);
            output[i + 1][3] = QString::number(temp_orders[i].geolocation.second);

            j = 4;
            for(auto it = temp_orders[i].other_dict.begin(); it != temp_orders[i].other_dict.end(); it++) {
                output[i + 1][j++] = it.key();
            }
        }
    }

    OpenStreetMapWrapper* InteractionService::get_api_wrapper(){
        return &api_wrapper;
    }
}
