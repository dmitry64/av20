#include "debuggui.h"
#include <QApplication>
#include <QObject>
#include <core.h>
#include "device/definitions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<AScan>("AScan");
    qRegisterMetaType<TVG>("TVG");
    Core * core = new Core();
    DebugGUI w;

    w.setCore(core);

    //QObject::connect(core,SIGNAL(debug(int)), &w, SLOT(debug(int)));
    QObject::connect(core,SIGNAL(drawAscan(AScan)), &w, SLOT(onAScan(AScan)));
    QObject::connect(core,SIGNAL(drawTVG(TVG)), &w,SLOT(onTVG(TVG)));

    //QObject::connect(core,SIGNAL(channelChanged(uint8_t)),&w,SLOT(onChannelChanged(uint8_t)));

    QObject::connect(core,SIGNAL(connection(bool)), &w, SLOT(onConnectionStatusChanged(bool)));
    QObject::connect(core,SIGNAL(connectionError(bool)), &w, SLOT(onErrorStatusChanged(bool)));
    QObject::connect(core,SIGNAL(deviceError(bool)), &w, SLOT(onDeviceErrorStatusChanged(bool)));
    QObject::connect(core,SIGNAL(deviceOverheat(bool)), &w, SLOT(onDeviceOverheatStatusChanged(bool)));
    QObject::connect(core,SIGNAL(deviceReady(bool)), &w, SLOT(onDeviceReadyStatusChanged(bool)));

    core->start();
    w.show();

    return a.exec();
}
