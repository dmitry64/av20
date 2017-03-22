#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>
#include <QDir>
#include "device/commonfunctions.h"

class Filesystem
{

    QStringList getFilesList(QString path);
    void createStructure();
public:
    Filesystem();
    void initFilesystem();
    QString getRootPath();

    QString getDataPath();
    QString getMediaPath();
    QString getCalibrationsPath();

    QStringList getDataList();
    QStringList getCalibrationsList();
    QStringList getMediaList();

};

#endif // FILESYSTEM_H
