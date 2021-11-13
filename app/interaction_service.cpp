#include "interaction_service.h"
#include "utils/downloader.cpp"
#include <utils/order_parser.cpp>

#include <iostream> 
#include <fstream>  
#include <QString>

#include <algorithm>
#include <memory>
#include <string>

namespace XOptimizer {
	InteractionService::InteractionService()
	{
		QObject::connect(&downloader, &Downloader::finished, [this](bool sucess) {
			qDebug() << "Download status: " << sucess; 
			this->parse_map();
		});
	}

	void InteractionService::download_and_parse_map(const std::string &region, const std::string &department) {
		map_file_path = QString::fromStdString("./" + region + "_" + department + ".pbf");
		downloader.download(region, department, map_file_path);
	}

	void InteractionService::parse_map() {
		std::shared_ptr<std::ifstream> map_stream = std::make_shared<std::ifstream>(map_file_path.toStdString());
 		PBFParser::PBFParser parser(map_stream);

		map_file_ptr = parser.parse();
	}

	void InteractionService::read_csv(QFile* file) {
		file_to_order(file, orders);
	}
}
