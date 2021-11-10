#include "interaction_service.h"
#include "utils/downloader.cpp"

#include <iostream> 
#include <fstream>  
#include <QString>

#include <algorithm>
#include <memory>
#include <string>

InteractionService::InteractionService()
{
	QObject::connect(&downloader, &Downloader::finished, [](bool sucess) {
		qDebug() << "Download status: " << sucess; 
	});
}

void InteractionService::download_and_parse_map(const std::string &region, const std::string &department) {
	map_file_path = QString::fromStdString(region + "_" + department + ".pbf");
	downloader.download(region, department, map_file_path);
}
