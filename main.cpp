#include "debuggui.h"
#include <QApplication>
#include <QObject>
#include <core.h>
#include "device/definitions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QSharedPointer<DisplayPackage> >("QSharedPointer<DisplayPackage>");
    qRegisterMetaType<QSharedPointer<AScanDrawData> >("QSharedPointer<AScanDrawData>");
    qRegisterMetaType<QSharedPointer<BScanDrawData> >("QSharedPointer<BScanDrawData>");
    qRegisterMetaType<Channel>("Channel");
    qRegisterMetaType<Gate>("Gate");
    qRegisterMetaType<TVG>("TVG");
    Core * core = new Core();
    DebugGUI w;

    w.setCore(core);

    //QObject::connect(core,SIGNAL(debug(int)), &w, SLOT(debug(int)));
    //QObject::connect(core,SIGNAL(drawAscan(QSharedPointer<AScanDrawData>)), &w, SLOT(onAScan(QSharedPointer<AScanDrawData>)));
    //QObject::connect(core,SIGNAL(drawBscan(QSharedPointer<BScanDrawData>)), &w, SLOT(onBScan(QSharedPointer<BScanDrawData>)));
    QObject::connect(core,SIGNAL(drawTVG(TVG)), &w,SLOT(onTVG(TVG)));
    QObject::connect(core,SIGNAL(channelChanged(Channel)),&w, SLOT(onChannelChanged(Channel)));
    QObject::connect(core,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), &w, SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)),Qt::ConnectionType::QueuedConnection); //SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    //QObject::connect(core,SIGNAL(channelChanged(uint8_t)),&w,SLOT(onChannelChanged(uint8_t)));

    //QObject::connect(core,SIGNAL(connection(bool)), &w, SLOT(onConnectionStatusChanged(bool)));
    //QObject::connect(core,SIGNAL(connectionError(bool)), &w, SLOT(onErrorStatusChanged(bool)));
    //QObject::connect(core,SIGNAL(deviceError(bool)), &w, SLOT(onDeviceErrorStatusChanged(bool)));
    //QObject::connect(core,SIGNAL(deviceOverheat(bool)), &w, SLOT(onDeviceOverheatStatusChanged(bool)));
    //QObject::connect(core,SIGNAL(deviceReady(bool)), &w, SLOT(onDeviceReadyStatusChanged(bool)));

    core->start();
    w.showFullScreen();

    return a.exec();
}
