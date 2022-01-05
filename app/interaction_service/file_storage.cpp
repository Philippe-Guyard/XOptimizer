#include "file_storage.h"
#include <QMap>
#include <QFileInfo>
#include <QSysInfo>
#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QResource>
#include <QTextStream>

bool make_subfolder(QDir base, QString subfolder) {
    if (base.exists(subfolder)) {
        return true;
    }
    else {
        base.mkdir(subfolder);
        return false;
    }
}

FileStorage::FileStorage() {
    QDir home = QDir::home();
    QString subfolder = "XOptimizer";
    QString maps_subfolder = subfolder + "/maps";
    make_subfolder(home, subfolder);
    make_subfolder(home, maps_subfolder);
    make_subfolder(home, subfolder + "/orders");

    base_folder = home.absolutePath() + "/" + subfolder;
    maps_base_folder = home.absolutePath() + "/" + maps_subfolder;
}

QString FileStorage::descriptor_to_map(QString region, QString department) {
    return region + "_" + department + "osm.pbf";
}

QString FileStorage::get_save_path_from_map_name(QString region, QString department) {
    return QDir::toNativeSeparators(maps_base_folder + "/" + descriptor_to_map(region, department));
}

QString FileStorage::get_save_path_from_csv(QString path) {
    QFileInfo f_info(path);
    return QDir::toNativeSeparators(base_folder + "/orders/" + f_info.fileName());
}

bool FileStorage::is_map_saved(QString region, QString department) {
    return QFileInfo::exists(maps_base_folder + "/" + descriptor_to_map(region, department));
}

/*
//this saves a copy of the
QString construct_build_path(){
    QString s = QDir::separator();
    return QDir::homePath() + s + "XOptimizer";
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
*/
