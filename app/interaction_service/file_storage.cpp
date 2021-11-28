#include "file_storage.h"
#include <QMap>
#include <QFileInfo>
#include <QSysInfo>


//https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html#//apple_ref/doc/uid/TP40010672-CH2-SW1
//https://doc.qt.io/qt-5/qfileinfo.html#filePath


//function implemented for testing
void FileStorage::save_map(std::string map_name, QFile* map){
    FiledictMaps[map_name] = map;
};
//For maps

bool FileStorage::is_map_saved(std::string map_name){
    return FiledictMaps.contains(map_name);
}

/*
std::string FileStorage::get_save_path(std::string region,std::string department){//this could be mapname
    std::string filepath;

    filepath = "./" + region + "_" + department + ".pbf";

    return filepath;

}
*/

QString FileStorage::get_save_path_from_map_name(std::string map_name){//this could be mapname
    QFile* map = FiledictMaps[map_name];

    QFileInfo fileinfo = QFileInfo(*map);

    QString path = fileinfo.absoluteFilePath();

    return path;
}

QFile* FileStorage::read_map(std::string map_name){
    return FiledictMaps[map_name];
}

QList<std::string> FileStorage::get_all_map_names(){
    return FiledictMaps.keys();}

//For CSV files
QList<std::string> FileStorage::get_all_csv_names(){
    return FiledictCSV.keys();

}


QFile* FileStorage::read_csv_by_name(std::string name){
    return FiledictCSV[name];
}

QString FileStorage::get_save_path_from_csv_name(std::string name){//this could be mapname
    QFile* csv = FiledictCSV[name];

    QFileInfo fileinfo = QFileInfo(*csv);

    QString path = fileinfo.filePath();

    return path;

}

