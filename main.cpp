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
    QObject::connect(core,SIGNAL(drawTVG(TVG)), w.getAscanWidget(),SLOT(onTVG(TVG)));

    QObject::connect(core,SIGNAL(debug(int)), &w, SLOT(debug(int)));
    QObject::connect(core,SIGNAL(drawAscan(AScan)), w.getAscanWidget(), SLOT(onAScan(AScan)));

    QObject::connect(core,SIGNAL(connectionStatusChanged(bool)), &w, SLOT(onConnectionStatusChanged(bool)));
    QObject::connect(core,SIGNAL(errorStatusChanged(bool)), &w, SLOT(onErrorStatusChanged(bool)));


    core->start();
    w.show();

    return a.exec();
}
