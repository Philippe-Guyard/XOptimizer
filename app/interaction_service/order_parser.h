#ifndef ORDER_PARSER_H
#define ORDER_PARSER_H

#endif // ORDER_PARSER_H
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QtDebug>
#include <QMap>
#include <QVector>
#pragma once

class Order{
public:
  Order(){}
  void set_id(int id){
      this->id = id;
      qDebug()<< "set id";
  }
  void set_location(QString location){
      this->location = location;
      qDebug()<<"set location";
  }
  void set_geolocation(QString geo){
      this->geolocation = geo;
      qDebug() << "set Geolocation";
  }
  void set_other(QString header,QString value){
      // overloads the value if header already exists
      this->other_dict.insert(header,value);
      qDebug() << "set other to key,value:" << header << ", " << value;
  }
private:
  int id; //order ID
  QString location; //order geolocation
  QString geolocation;
  QMap<QString , QString> other_dict;
};
