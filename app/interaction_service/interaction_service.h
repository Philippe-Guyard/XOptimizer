#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H
#include <QMainWindow>

//#include <utils/parser/pbf-parser.h>
//#include <utils/parser/pbf-parser.cpp>
#include <utils/downloader/downloader.cpp>

QT_BEGIN_NAMESPACE
namespace XOptimiser::interaction_service{


//GENERALFUNCTION TEMPLATES


//END GENERALFUNCTION TEMPLATES

//MAIN RETURN CLASS
class interaction_service{

public:
   interaction_service();
   interaction_service(const std::string Region,  const std::string Department, const QString Orders);//CALLS DOWNLOADER AND PARSER and puts them into the arguments
   ~interaction_service();

   //bool is_downloader_data_valid();

   void Download_Parse();

   //void get_final_output();

private:
    const std::string Region;
    const std::string Department;
    //based on region and department
    std::shared_ptr<std::istream> GraphInputStream;

    //to be used later
    std::vector<int> OrderNumbers;
    std::vector<std::string>  Deliverylist;
    std::string Vehicle;




};

};
QT_END_NAMESPACE




