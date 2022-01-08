#include "interaction_service.h"
#include <parser/pbf-parser.h>

#include <iostream>
#include <fstream>
#include <QString>

#include <algorithm>
#include <memory>
#include <chrono>
#include <string>
#include <thread>


template<typename R>
bool is_ready(std::future<R> const& f) {
    return f.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready;
}


namespace XOptimizer {
InteractionService::InteractionService() {
    m_file_storage = std::make_unique<FileStorage>();
}

InteractionService::~InteractionService() {

}

void InteractionService::download_and_parse_map(const std::string &region, const std::string &department, std::optional<std::function<void(qint64, qint64)>> download_callback) {
    qDebug() << "Download and parse started.";

    map_file_path = m_file_storage->get_save_path_from_map_name(QString::fromStdString(region), QString::fromStdString(department));
    if (m_file_storage->is_map_saved(QString::fromStdString(region), QString::fromStdString(department))) {
        this->start_parsing_thread();
    }
    else {
        auto reply = api_wrapper.download(region, department, map_file_path);
        QObject::connect(reply, &QNetworkReply::finished, [this]() {
            qDebug() << "Download finished.";
            this->start_parsing_thread();
            qDebug() << "Download exit.";
        });
        if (download_callback.has_value()) {
            QObject::connect(reply, &QNetworkReply::downloadProgress, download_callback.value());
        }
        qDebug() << "Download and parse ended.";
    }
}

void InteractionService::start_parsing_thread() {
    this->parsing_thread = std::async(std::launch::async, [this]() {
        std::shared_ptr<std::ifstream> map_stream = std::make_shared<std::ifstream>(map_file_path.toStdString());
        PBFParser::PBFParser parser(map_stream);

        auto start = std::chrono::high_resolution_clock::now();
        this->map_file_ptr = parser.parse();
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Parsing took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        this->map = this->map_file_ptr->to_map();
        end = std::chrono::high_resolution_clock::now();
        std::cout << "to_map took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

        map_stream->close();
    });
}

void InteractionService::optimize_csv(QFile* file) {
    QString new_path = m_file_storage->get_save_path_from_csv(file->fileName());
    QFile new_file(new_path);

    //TODO: Uncomment this
    //api_wrapper.searchCSV(file, &new_file);
    file_to_order(file, orders);
    start_optimization_thread();
}

void InteractionService::start_optimization_thread() {
    this->optimization_thread = std::async(std::launch::async, [this]() {
        while (!is_ready(this->parsing_thread))
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        VertexData* orders_vdata = new VertexData[this->orders.size()];       
        std::vector<int> orders_indices;
        //std::unordered_map<int, int> node_to_order;
        for(int i = 0; i < this->orders.size(); ++i) {
            orders_vdata[i] = VertexData(this->orders[i].geolocation, static_cast<int>(this->orders[i].is_inventory));
            int node_idx = map->brute_force_closest_vertex_index(orders_vdata[i]);
            orders_indices.push_back(node_idx);
            //node_to_order[node_idx] = i;
        }

        auto distances = this->map->find_distances(orders_indices);
        auto g = Graph(this->orders.size(), orders_vdata, distances);
        auto optimal_circuit = g.optimal_routing_all();
        //For now we assume only 1 inventory
        assert(optimal_circuit.size() == 1);
        for(auto it = optimal_circuit[0].begin(); it != optimal_circuit[0].end(); it++) {
            this->optimized_orders.push_back(this->orders[*it]);
        }

        delete[] orders_vdata;
    });
}

bool InteractionService::get_optimized_orders(QVector<QVector<QString>> &output_table, QVector<std::pair<double, double>>& output_path) {
    if (is_ready(this->optimization_thread)) {
        orders_to_table(this->optimized_orders, output_table);
        for(auto order : this->optimized_orders)
            output_path.push_back(order.geolocation);

        return true;
    }
    else
        return false;
}

void InteractionService::read_csv_as_table(QFile *file, QVector<QVector<QString>> &output) {
    QVector<Order> temp_orders;
    file_to_order(file, temp_orders);
    orders_to_table(temp_orders, output);
}

OpenStreetMapWrapper* InteractionService::get_api_wrapper(){
    return &api_wrapper;
}
}
