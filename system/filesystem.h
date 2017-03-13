#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QString>

#include "device/commonfunctions.h"

class Filesystem
{

public:
    Filesystem();
    void initFilesystem();
    QString getRootPath();

    QString getDataPath();
    QString getMediaPath();
    QString getCalibrationsPath();

};

#endif // FILESYSTEM_H
