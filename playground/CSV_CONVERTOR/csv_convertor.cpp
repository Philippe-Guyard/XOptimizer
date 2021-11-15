#include "csv_convertor.h"
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QtDebug>
#include <QMap>
#include <QVector>

#include <parser/pbf-parser.h>
#include <utils/downloader.cpp>
#include <utils/order_parser.cpp>
#include <utils/geocoder.cpp>


void order_to_address(QFile *out_file, QVector<Order>& order_list){
    //open outfile
    if(!out_file->open(QFile::ReadWrite | QFile::Text)){
            qDebug() << "Could not open file for writing";
        }

   out_file->open(QFile::ReadWrite | QFile::Text);

//write all locations in outfile
    for (int i = 0; i < order_list.size(); ++i){
        QString address_to_write = order_list.at(i).location;

        QTextStream out(out_file);
            out << address_to_write << '\n';
    }

    out_file->close();
    }


void adressess_to_geolocation(QFile *out_file){
    *buildMultpart(out_file)
}


QFile* order_to_address_to_geolocation(QFile *out_file, QVector<Order>& order_list){
    file_to_order(out_file, order_list);
    order_to_address(out_file,order_list);
    *buildMultpart(out_file);
    return out_file;
}

