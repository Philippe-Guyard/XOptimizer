#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include<QFile>

class FileStorage {
public:
    FileStorage();

    bool is_map_saved(std::string map_name);
    void save_map(std::string map_name);
    QFile* read_map(std::string map_name);

    std::vector<std::string> get_all_csv_names();
    QFile* read_csv_by_name(std::string name);
};

#endif // FILE_STORAGE_H
