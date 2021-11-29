#include "interaction_service.h"
#include <parser/pbf-parser.h>

#include <iostream>
#include <fstream>
#include <QString>

#include <algorithm>
#include <memory>
#include <string>

namespace XOptimizer {
    InteractionService::InteractionService() {

    }

    InteractionService::~InteractionService() {

    }

    void InteractionService::download_and_parse_map(const std::string &region, const std::string &department) {
//				map_file_path = QString::fromStdString("" + region + "_" + department + ".pbf");
        api_wrapper.download(region, department, map_file_path);
        //TODO: Uncomment this. For now we don't have an implementation of the parser yet so it is useless
        //parse_map();
    }

    void InteractionService::parse_map() {
        //TODO: Uncomment this. For now we don't have an implementation of the parser yet so it is useless
        /*
        std::shared_ptr<std::ifstream> map_stream = std::make_shared<std::ifstream>(map_file_path.toStdString());
        PBFParser::PBFParser parser(map_stream);

        map_file_ptr = parser.parse();
        */
    }

    void InteractionService::read_csv(QFile* file) {
        file_to_order(file, orders);
    }

		void InteractionService::set_map_file_path(QString path){
			map_file_path = path;
		}

		OpenStreetMapWrapper* InteractionService::get_api_wrapper(){
			return &api_wrapper;
		}
}
