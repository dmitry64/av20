#include "filesystem.h"


QStringList Filesystem::getFilesList(QString path)
{
    QDir directory(path);
    return directory.entryList(QDir::Files, QDir::Time);
}

void Filesystem::createStructure()
{
    QDir av20(getRootPath());
    QDir root("/");
    root.mkpath(getRootPath());
    av20.mkdir("data");
    av20.mkdir("media");
    av20.mkdir("calibrations");
    av20.mkdir("help");
    av20.mkdir("operators");
}

Filesystem::Filesystem()
{

}

void Filesystem::initFilesystem()
{
    logEvent("Filesystem","Ready");
    logEvent("Filesystem","Root path: "+getRootPath());
    QDir root(getRootPath());
    if(!root.exists()) {
        createStructure();
    }
}

QString Filesystem::getRootPath()
{
    return QDir::homePath() + "/av20";
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

QString Filesystem::getHelpPath()
{
    return getRootPath() + "/help";
}

QString Filesystem::getOperatorsPath()
{
    return getRootPath() + "/operators";
}

QStringList Filesystem::getDataList()
{
    return getFilesList(getDataPath());
}

QStringList Filesystem::getCalibrationsList()
{
    return getFilesList(getCalibrationsPath());
}

QStringList Filesystem::getMediaList()
{
    return getFilesList(getMediaPath());
}

QStringList Filesystem::getHelpList()
{
    return getFilesList(getHelpPath());
}
