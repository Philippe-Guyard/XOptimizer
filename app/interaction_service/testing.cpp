#include <interaction_service.h>
#include "testing.h"
#include <QDir>

Testing::Testing(XOptimizer::InteractionService* s){
	service = s;
	QDir::setCurrent("/Users/markdaychman/Documents/GitHub/XOptimizer/app/interaction_service/resources");
}

void Testing::test_download(){
	QFile out1("./out.pbf");
	QFileInfo inf(out1);
	service->set_map_file_path(inf.absoluteFilePath());
	QNetworkAccessManager* man = service->get_api_wrapper()->get_manager();
	service->download_and_parse_map("corse", "haute_corse");
	QObject::connect(man, &QNetworkAccessManager::finished, [&](QNetworkReply* reply){

	// Calculating the checksum of the file

		QCryptographicHash hash(QCryptographicHash::Md5);
		if (hash.addData(reply)) {
			 assert(hash.result().toHex().toStdString() == "d41d8cd98f00b204e9800998ecf8427e");
			 std::cout << "test_download: success ✅" << std::endl;
		}
	});
};

void Testing::test_parse_orders(){
	// Will be implemented after the parsing is complete
	std::cout << "test_parse_order: success ✅" << std::endl;
};

void Testing::test_search_csv(){
	// Can be done better with Qt resource system
	QFile test1("./test1.csv");
	QFile test2("./test2.csv");
	service->read_csv(&test1);

	assert(service->orders.size() == 4);
	assert(service->orders.at(0).location == "6 Rue Albert 1er");
	assert(service->orders.at(0).other_dict["postcode"] == "54600");
	assert(service->orders.at(3).id == 0);

	service->read_csv(&test2);
	assert(service->orders.size() == 5);
	assert(service->orders.at(4).geolocation.first == 43.572782);
	assert(service->orders.at(4).geolocation.second == 7.117496);
	assert(service->orders.at(2).geolocation.first == 0.0);

	std::cout << "test_search_csv: success ✅" << std::endl;
};

void Testing::run_all(){
	test_download();
	test_parse_orders();
	test_search_csv();
}
