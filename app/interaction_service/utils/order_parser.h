#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QtDebug>
#include <QMap>
#include <QVector>
#include <QString>
#pragma once


class Order{
  public:
    Order(){}
    void set_id(int id);
    void set_location(QString location);
    void set_longitude(double longitude);
    void set_latitude(double latitude);
    void set_other(QString header,QString value);
		int id; //order ID
		QString location; //order adress
		std::pair<double, double> geolocation;
		QMap<QString , QString> other_dict;
};


Order line_to_order(QString line, QVector<QString> header);
void file_to_order(QFile *file, QVector<Order>& order_list);
