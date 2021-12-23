//#include "interaction_service.h"
#include "testing.h"
#include <QDir>
#include "file_storage.h"
#include <iostream>
/*
Testing::Testing(XOptimizer::InteractionService* s){
	service = s;
    //QDir::setCurrent("/Users/markdaychman/Documents/GitHub/XOptimizer/app/interaction_service/resources");
}

void Testing::test_download(){
	QFile out1("./out.pbf");
    QFileInfo inf(out1);
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
*/
void Testing::test_filestorage(){
    FileStorage store;
    QString s = QDir::separator();
    /*
    QString path = QDir::homePath() + s + "Desktop" + s +"XOptimizer" + s + "app"+ s+ "interaction_service" +s+"test.csv";
    std::cout << path.toStdString()<< "\n";
    QFile file(path);
    QFile file2(path);*/

   // QFile file("/Users/johannaulin/Desktop/test.csv");
   // QFile file2("/Users/johannaulin/Desktop/test.csv");
    QFile file("." + s + "test1.csv");
    QFile file2("." + s + "test2.csv");
    //FileStorage store;'
    store.save_map("mappi", &file);
    store.save_map("mappi2", &file2);

    //FUNCTION TEST
    //TEST MAP
    std::cout << " All following tests are ultimately testing the methos to save and store the csv and pbf map files. OBS! Check if files are empty. Then incorrect path has been given" << "\n";
    std::cout << "1:is_map_saved and save_map"<< "\n";
    if (store.is_map_saved("mappi") && store.is_map_saved("mappi2")){
        std::cout << "test on is_map_saved: success ✅" << "\n";

    }
    if (store.FiledictMaps.contains("mappi")){
        QString item = store.FiledictMaps["mappi"];
        QFile f(item);
        f.open( QIODevice::WriteOnly|QIODevice::Append );
        if (f.pos() != 0){std::cout << "mappi saved and non empty: success ✅" << "\n";}
        else{std::cout << "ERROR: map saved but empty" << "\n";}
        f.close();
    }

     if (store.FiledictMaps.contains("mappi2")){
            QString item = store.FiledictMaps["mappi2"];
            QFile f(item);
            f.open( QIODevice::WriteOnly|QIODevice::Append );
            if (f.pos() != 0){std::cout << "mappi2 saved and non empty: success ✅" << "\n";}
            else{std::cout << "ERROR: mappi2 saved but empty" << "\n";}
            f.close();
     }


    std::cout << "2:get_save_path_from_map_name"<< "\n";
        std::cout << store.get_save_path_from_map_name("mappi").toStdString()<< "\n";

    std::cout << "3:read_map"<< "\n";
    std::cout << store.read_map("mappi")<< "\n";
    std::cout << "OBS! test to be implemented" << "\n";

    std::cout << "4:get_all_map_names"<< "\n";
    int k = 0;
    foreach( std::string item, store.get_all_map_names()){
        if (item == "mappi"){
            k+= 1;
        }

        if (item == "mappi2"){
           k+= 1;
        }

    }
    if (k == 2) {
       std::cout << "mappi saved : success ✅" << "\n";
}
    else{std::cout << "ERROR" << "\n";
    }




    std::cout << "5:construct_save_path_from_map_name"<< "\n";
    QString h= "here";
    QString t ="there";
    std::cout << store.construct_save_path(h, t).toStdString()<< "\n";

    //TEST CSV
    std::cout << "6:save csv"<< "\n";
    store.save_csv("csv1", &file);
    store.save_csv("csv2", &file2);
    if (store.FiledictCSV.contains("csv1")){
        QString item = store.FiledictCSV["csv1"];
        QFile f(item);
        f.open( QIODevice::WriteOnly|QIODevice::Append );
        if (f.pos() != 0){std::cout << "csv saved and non empty: success ✅" << "\n";}
        else{std::cout << "ERROR: csv saved but empty" << "\n";}
        f.close();
    }
    if (store.FiledictCSV.contains("csv2")){
        QString item = store.FiledictCSV["csv2"];
        QFile f(item);
        f.open( QIODevice::WriteOnly|QIODevice::Append );
        if (f.pos() != 0){std::cout << "csv2 saved and non empty: success ✅" << "\n";}
        else{std::cout << "ERROR: csv saved but empty" << "\n";}
        f.close();
    }

    std::cout << "7:get_all_csv_names"<< "\n";
    foreach( std::string item, store.get_all_csv_names()){
        if (item == "csv1"){

            std::cout << "csv1 saved : success ✅" << "\n";
        }

        if (item == "csv2"){
                         std::cout << "csv2 saved : success ✅" << "\n";
        }

}
}

void Testing::run_all(){
    test_download();
    test_parse_orders();
    test_search_csv();
    test_filestorage();
}


