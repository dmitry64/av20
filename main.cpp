#include "ui/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>
#include <core.h>
#include "common/definitions.h"
#include "system/system.h"
#include "device/calibrationmanager.h"
#include "common/commonfunctions.h"
#include "ui/splashscreen.h"
#define DEFAULT_MODE

#ifdef DEFAULT_MODE
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SplashScreen * splashScreen = new SplashScreen();
    splashScreen->show();
    QApplication::processEvents();
    splashScreen->progressChanged(5);
    splashScreen->setMessage("Starting Avicon-20...");
    logEvent("Main","Avicon-20 starting...");

    qRegisterMetaType<QSharedPointer<DisplayPackage> >("QSharedPointer<DisplayPackage>");
    qRegisterMetaType<QSharedPointer<AScanDrawData> >("QSharedPointer<AScanDrawData>");
    qRegisterMetaType<QSharedPointer<BScanDrawData> >("QSharedPointer<BScanDrawData>");
    qRegisterMetaType<Channel>("Channel");
    splashScreen->progressChanged(13);
    splashScreen->setMessage("Loading system...");
    System * system = System::getInstance();
    splashScreen->progressChanged(15);
    system->init();
    splashScreen->progressChanged(21);

    splashScreen->setMessage("Loading calibrations...");
    CalibrationManager * calibrationManager = new CalibrationManager();
    splashScreen->progressChanged(23);
    calibrationManager->init();
    splashScreen->progressChanged(28);

    calibrationManager->setSavePath(system->getFilesystem()->getCalibrationsPath());
    splashScreen->progressChanged(29);
    calibrationManager->loadAll();
    splashScreen->progressChanged(35);

    splashScreen->setMessage("Loading mode manager...");
    ModeManager * modeManager = new ModeManager();
    splashScreen->progressChanged(39);
    modeManager->init();
    splashScreen->progressChanged(46);

    splashScreen->setMessage("Loading core...");
    Core * core = new Core(modeManager, calibrationManager);
    splashScreen->progressChanged(58);
    splashScreen->setMessage("Loading graphical interface...");
    MainWindow * mainWindow = new MainWindow();
    splashScreen->progressChanged(67);

    QObject::connect(core,SIGNAL(displayVersion(QString)),system, SLOT(onDeviceVersionReady(QString)));
    QObject::connect(core,SIGNAL(channelChanged(Channel)),mainWindow, SLOT(onChannelChanged(Channel)));
    QObject::connect(core,SIGNAL(modeChanged()),mainWindow, SLOT(onModeChanged()));
    QObject::connect(core,SIGNAL(calibrationChanged()),mainWindow, SLOT(onCalibrationChanged()));
    QObject::connect(core,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), mainWindow, SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)),Qt::ConnectionType::QueuedConnection); //SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    QObject::connect(core,SIGNAL(registrationStateChanged(bool)),mainWindow,SIGNAL(registrationStateChanged(bool)));


    QObject::connect(core,SIGNAL(deviceOverheatEnable()),mainWindow, SLOT(onDeviceOverheatEnable()));
    QObject::connect(core,SIGNAL(deviceOverheatDisable()),mainWindow, SLOT(onDeviceOverheatDisable()));
    QObject::connect(core,SIGNAL(deviceErrorEnable()),mainWindow, SLOT(onDeviceErrorEnable()));
    QObject::connect(core,SIGNAL(deviceErrorDisable()),mainWindow, SLOT(onDeviceErrorDisable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorEnable()),mainWindow, SLOT(onDeviceConnectionErrorEnable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorDisable()),mainWindow, SLOT(onDeviceConnectionErrorDisable()));

    splashScreen->progressChanged(78);
    splashScreen->setMessage("Starting core...");
    QThread* thread = new QThread();

    core->moveToThread(thread);
    //connect(core, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    QObject::connect(thread, SIGNAL(started()), core, SLOT(work()));
    QObject::connect(core, SIGNAL(finished()), thread, SLOT(quit()));
    //QObject::connect(core, SIGNAL(finished()), core, SLOT(deleteLater()));
    //QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    splashScreen->progressChanged(88);
    thread->start();
    thread->setPriority(QThread::HighPriority);

    mainWindow->setCore(core);
    splashScreen->progressChanged(92);
    mainWindow->init();
    splashScreen->setMessage("Loading finished.");
    //mainWindow->move(-1000,0);
    //mainWindow->showFullScreen();
    splashScreen->progressChanged(100);
    splashScreen->hide();
    mainWindow->show();

    logEvent("Main","Starting exec loop");
    int retcode = a.exec();
    logEvent("Main","Exit");
    return retcode;
}
#endif
