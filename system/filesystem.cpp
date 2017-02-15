#include "filesystem.h"

Filesystem::Filesystem()
{

}

void Filesystem::initFilesystem()
{

}

QString Filesystem::getRootPath()
{
    return "/home/root";
}

QString Filesystem::getDataPath()
{
    return getRootPath() + "/data";
}

QString Filesystem::getMediaPath()
{
    return getRootPath() + "/media";
}

QString Filesystem::getCalibrationsPath()
{
    return getRootPath() + "/calibrations";
}
