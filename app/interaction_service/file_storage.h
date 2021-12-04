#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include<QFile>
#include<QList>
#include<QMap>

class FileStorage {
public:
    //FileStorage();
    FileStorage(){
                FiledictMaps = QMap<std::string, QFile*>();
                FiledictCSV = QMap<std::string, QFile*>();
                 }

    void save_map(std::string map_name, QFile* map);

    //For Map/PBF files
    QMap<std::string, QFile*> FiledictMaps;

    std::string get_save_path(std::string region,std::string department);
    QString get_save_path_from_map_name(std::string map_name);


    bool is_map_saved(std::string map_name);

    QFile* read_map(std::string map_name);

    QList<std::string> get_all_map_names();
    //For CSV files

    QMap<std::string, QFile*> FiledictCSV;

    QList<std::string> get_all_csv_names();

    QFile* read_csv_by_name(std::string name);

    QString get_save_path_from_csv_name(std::string name);

};

#endif // FILE_STORAGE_H
