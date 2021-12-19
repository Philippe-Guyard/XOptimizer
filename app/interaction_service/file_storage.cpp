#include "file_storage.h"
#include <QMap>
#include <QFileInfo>
#include <QSysInfo>
#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QResource>

//this saves a copy of the
QString construct_build_path(){
    QString s = QDir::separator();
    return QDir::homePath() + s;
    /*

    QString p = QDir::currentPath();

    QString s = QDir::separator();

    QList<QString> pathlist = p.split(s);
    int found = 0;
    foreach( QString item, pathlist)
         if(item.contains(QString(".app"))){
             pathlist.removeOne(item);
             found = 1;
         }
         else if(found ==1){
             pathlist.removeOne(item);

         }
    QString path; //(s)

    foreach( QString elem, pathlist)
        path.append(elem+s);

    return path;
*/
};

void FileStorage::save_map(std::string map_name, QFile* map){
    QString path = construct_build_path();
    path.append("MAP_Storage");

    QString s = QDir::separator();
    path.append(s);

    QString name;
    name = name.fromStdString(map_name);
    path.append(name);

    QFile newmap(path);

    newmap.open(QIODevice::WriteOnly);
    map->open(QFile::ReadOnly);

    QTextStream instream(map);
    QTextStream out(&newmap);


    QString line = instream.readLine();

    while (!instream.atEnd()){
           out << line << "\n";
           line = instream.readLine();
       }
    map->close();
    newmap.close();

    //store copy in dictionary
    FiledictMaps[map_name] = path;

};

bool FileStorage::is_map_saved(std::string map_name){
    return FiledictMaps.contains(map_name);

}

QString FileStorage::construct_save_path(QString region, QString department){//this could be mapname
    QString path = construct_build_path();
    path.append("MAP_Storage");
    QString sl = (".");
    QString s = QDir::separator();
    path.append(s);
    path.append(region);
    path.append(sl);
    path.append(department);

    return path;
}

QString FileStorage::get_save_path_from_map_name(std::string map_name){

    if(is_map_saved(map_name)){

    QString path = FiledictMaps[map_name];
    return path;

    }

    else{
        QString path("error, map is not saved");
        return path;
    }
}

QFile* FileStorage::read_map(std::string map_name){
    QString path = FiledictMaps[map_name];
    QFile map(path);
    return &map;
}

QList<std::string> FileStorage::get_all_map_names(){
    return FiledictMaps.keys();
}


//For CSV files
void FileStorage::save_csv(std::string csv_name, QFile* csv){

    QString path = construct_build_path();
    path.append("CSV_Storage");

    QString s = QDir::separator();
    path.append(s);

    QString name;
    name = name.fromStdString(csv_name);
    path.append(name);

    QFile newcsv(path);
    newcsv.open(QFile::WriteOnly);
    csv->open(QFile::ReadOnly);

    QTextStream instream(csv);
    QTextStream out(&newcsv);
    QString line = instream.readLine();

    while (!instream.atEnd()){
           out << line << "\n";
           line = instream.readLine();
       }
    csv->close();
    newcsv.close();


    //store copy in dictionary
    FiledictCSV[csv_name] = path;


}

QList<std::string> FileStorage::get_all_csv_names(){
    return FiledictCSV.keys();
}


QFile* FileStorage::read_csv_by_name(std::string name){
    QString path = FiledictCSV[name];
    QFile csv(path);
    return &csv;
}


QString FileStorage::get_save_path_from_csv_name(std::string name){
    QString path= FiledictMaps[name];
    return path;
}

