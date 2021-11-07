#ifndef INTERACTION_SERVICE_H
#define INTERACTION_SERVICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace XOptimiser::interaction_service{

//SUB CLASSES

class city_name{


};

class order_number{

};

class delivery_route_result{

};

class vehicle_id{

};

//GENERALFUNCTION TEMPLATES


//END GENERALFUNCTION TEMPLATES

//MAIN RETURN CLASS
class final_output{

public:
   final_output();//CALLS DOWNLOADER AND PARSER and puts them into the arguments
   ~final_output();
   void get_final_output();



private:
    city_name City;
    order_number OrderNumber;
    delivery_route_result Deliverylist;
    vehicle_id Vehicle;


};

};
QT_END_NAMESPACE




