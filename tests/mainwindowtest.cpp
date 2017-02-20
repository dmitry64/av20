#include "mainwindowtest.h"
#include "testdatagenerators.h"
#include "system/system.h"

MainWindowTest::MainWindowTest(QObject *parent) : QObject(parent)
{
    System * system = System::getInstance();
    system->init();

    qRegisterMetaType<QSharedPointer<DisplayPackage> >("QSharedPointer<DisplayPackage>");
    qRegisterMetaType<QSharedPointer<AScanDrawData> >("QSharedPointer<AScanDrawData>");
    qRegisterMetaType<QSharedPointer<BScanDrawData> >("QSharedPointer<BScanDrawData>");
    qRegisterMetaType<Channel*>("Channel*");
}

void MainWindowTest::simpleCreateTest()
{
    MainWindow * wnd = new MainWindow();
    delete wnd;
}

void MainWindowTest::simpleCreateWithCore()
{
    MainWindow * wnd = new MainWindow();

    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);
    core->start();

    wnd->setCore(core);
    wnd->init();

    wnd->show();

    QThread::msleep(20);

    wnd->hide();


    core->stopCore();
    delete core;
    delete manager;
    delete calib;

    delete wnd;
}

void MainWindowTest::simpleMenuClicking()
{
    MainWindow * wnd = new MainWindow();

    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);

    QObject::connect(core,SIGNAL(channelChanged(Channel*)),wnd, SLOT(onChannelChanged(Channel*)));
    QObject::connect(core,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), wnd, SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)),Qt::ConnectionType::QueuedConnection); //SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    QObject::connect(core,SIGNAL(deviceOverheatEnable()),wnd, SLOT(onDeviceOverheatEnable()));
    QObject::connect(core,SIGNAL(deviceOverheatDisable()),wnd, SLOT(onDeviceOverheatDisable()));
    QObject::connect(core,SIGNAL(deviceErrorEnable()),wnd, SLOT(onDeviceErrorEnable()));
    QObject::connect(core,SIGNAL(deviceErrorDisable()),wnd, SLOT(onDeviceErrorDisable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorEnable()),wnd, SLOT(onDeviceConnectionErrorEnable()));
    QObject::connect(core,SIGNAL(deviceConnectionErrorDisable()),wnd, SLOT(onDeviceConnectionErrorDisable()));

    core->start();

    wnd->setCore(core);
    wnd->init();

    wnd->show();
    for(int j=0; j<100; j++) {
        QApplication::processEvents();
    }

    QThread::msleep(300);
    int step = static_cast<double>(wnd->width())/7.0;
    //qDebug() << "step" <<step;
    int height = wnd->height();
    QPoint center = QPoint(wnd->width()/2,wnd->height()/2);
    for(int i=0; i<7; i++) {
        QApplication::processEvents();

        QPoint p = QPoint(30 + i * step, height - 20);

        QTest::mouseMove(wnd,p,100);
        QWidget * wid = wnd->childAt(p);
        QApplication::processEvents();
        QTest::mouseClick(wid,Qt::MouseButton::LeftButton,Qt::KeyboardModifier::NoModifier,QPoint(0,0),30);
        for(int j=0; j<55; j++) {
            QApplication::processEvents();
            QThread::usleep(20);
        }
        QTest::mouseClick(wid,Qt::MouseButton::LeftButton,Qt::KeyboardModifier::NoModifier,QPoint(0,0),30);
    }
    QThread::msleep(30);

    wnd->hide();

    core->stopCore();
    delete core;
    delete manager;
    delete calib;

    delete wnd;
}
