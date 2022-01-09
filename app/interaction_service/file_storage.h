#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include<QFile>
#include<QList>
#include<QMap>
#include <QResource>
#include <QDir>
#include <QSet>

class FileStorage {
private:
    QString base_folder;
    QString maps_base_folder;

    QString descriptor_to_map(QString, QString);
public:
    FileStorage();

    QString get_save_path_from_map_name(QString region, QString department);
    QString get_save_path_from_csv(QString path);
    bool is_map_saved(QString, QString);
};

#endif // FILE_STORAGE_H
