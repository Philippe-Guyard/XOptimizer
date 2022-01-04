#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include<QFile>
#include<QList>
#include<QMap>
#include <QResource>
#include <QDir>

class FileStorage {
private:
    QString base_folder;
public:
    FileStorage();

    QString get_save_path_from_map_name(QString region, QString department);
    QString get_save_path_from_csv(QString path);
};

#endif // FILE_STORAGE_H
