#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>
#include <QDir>
#include "common/commonfunctions.h"

class Filesystem
{
    static QStringList getFilesList(QString path);
    static void createStructure();
public:
    Filesystem();
    static void initFilesystem();
    static QString getRootPath();

    static QString getDataPath();
    static QString getMediaPath();
    static QString getCalibrationsPath();
    static QString getHelpPath();
    static QString getOperatorsPath();

    static QStringList getDataList();
    static QStringList getCalibrationsList();
    static QStringList getMediaList();
    static QStringList getHelpList();
};

#endif // FILESYSTEM_H
