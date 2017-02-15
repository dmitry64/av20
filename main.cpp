#include "debuggui.h"
#include "ui/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>
#include <core.h>
#include "device/definitions.h"
#include "system/system.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QWidget splashsceen;
    //splashsceen.setGeometry(0,0,1024,600);
    //splashsceen.show();
    qRegisterMetaType<QSharedPointer<DisplayPackage> >("QSharedPointer<DisplayPackage>");
    qRegisterMetaType<QSharedPointer<AScanDrawData> >("QSharedPointer<AScanDrawData>");
    qRegisterMetaType<QSharedPointer<BScanDrawData> >("QSharedPointer<BScanDrawData>");
    qRegisterMetaType<Channel>("Channel");

    System * system = System::getInstance();
    system->init();

    Core * core = new Core();
    MainWindow * mainWindow = new MainWindow();

    QObject::connect(core,SIGNAL(channelChanged(Channel)),mainWindow, SLOT(onChannelChanged(Channel)));
    QObject::connect(core,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), mainWindow, SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)),Qt::ConnectionType::QueuedConnection); //SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    QObject::connect(core,SIGNAL(deviceOverheatEnable()),mainWindow, SLOT(onDeviceOverheatEnable()));
    QObject::connect(core,SIGNAL(deviceOverheatDisable()),mainWindow, SLOT(onDeviceOverheatDisable()));
    QObject::connect(core,SIGNAL(deviceErrorEnable()),mainWindow, SLOT(onDeviceErrorEnable()));
    QObject::connect(core,SIGNAL(deviceErrorDisable()),mainWindow, SLOT(onDeviceErrorDisable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorEnable()),mainWindow, SLOT(onDeviceConnectionErrorEnable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorDisable()),mainWindow, SLOT(onDeviceConnectionErrorDisable()));


    core->start();

    mainWindow->setCore(core);

    //splashsceen.hide();
    mainWindow->show();

    return a.exec();
}
