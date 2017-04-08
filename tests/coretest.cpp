#include "coretest.h"
#include "device/tvg/tvgtwopoints.h"
#include "testdatagenerators.h"

CoreTest::CoreTest(QObject *parent) : QObject(parent)
{

}

void CoreTest::coreCreate()
{
    CalibrationManager * calibrationManager = new CalibrationManager();
    calibrationManager->init();

    ModeManager * modeManager = new ModeManager();
    modeManager->init();
    Core * core = new Core(modeManager,calibrationManager);

    core->start();

    core->stopCore();
    delete core;
    delete modeManager;
    delete calibrationManager;
}

void CoreTest::coreSimpleConfig()
{
    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);

    core->start();
    core->stopCore();
    delete core;
    delete manager;
    delete calib;
}

void CoreTest::coreCommunicationSimple()
{
    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);
    core->start();

    Gate gate;
    gate._start = 23;
    gate._finish = 32;
    gate._id = 1;
    gate._level = 20;

    core->addGate(0,gate);

    core->getCalibrationsSnapshot();
    core->getTactTableSnapshot();

    gate._finish = 77;
    gate._start = 20;
    gate._level = 99;
    core->modifyGate(0,gate);
    TVGTwoPoints * simple = new TVGTwoPoints(65.0,35.0,70.0,32.0,25.0);
    core->setTVG(0,simple);
    delete simple;

    QThread::msleep(200);

    core->stopCore();
    delete core;
    delete manager;
    delete calib;
}

void CoreTest::coreGateSetup()
{
    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);
    core->start();

    Gate gate;
    gate._start = 23;
    gate._finish = 32;
    gate._id = 1;
    gate._level = 20;
    core->addGate(0,gate);

    QThread::usleep(500);

    gate._start = 1;
    gate._finish = 1;
    gate._id = 2;
    gate._level = 1;
    core->addGate(0,gate);

    QThread::usleep(500);

    gate._start = 99;
    gate._finish = 99;
    gate._id = 0;
    gate._level = 80;
    core->addGate(1,gate);

    QThread::usleep(500);

    gate._start = 200;
    gate._finish = 200;
    gate._id = 1;
    gate._level = 0;
    core->addGate(2,gate);

    QThread::usleep(500);

    gate._start = 0;
    gate._finish = 200;
    gate._id = 0;
    gate._level = 0;
    core->addGate(3,gate);

    QThread::usleep(500);

    gate._start = 55;
    gate._finish = 55;
    gate._id = 0;
    gate._level = 0;
    core->addGate(4,gate);

    QThread::usleep(500);

    gate._start = 0;
    gate._finish = 0;
    gate._id = 0;
    gate._level = 0;
    core->addGate(5,gate);

    QThread::usleep(500);

    gate._start = 200;
    gate._finish = 200;
    gate._id = 99;
    gate._level = 79;
    core->addGate(6,gate);

    QThread::usleep(500);

    gate._start = 1;
    gate._finish = 1;
    gate._id = 1;
    gate._level = 1;
    core->addGate(7,gate);

    QThread::usleep(500);

    core->getCalibrationsSnapshot();
    core->getTactTableSnapshot();

    gate._finish = 77;
    gate._start = 20;
    gate._level = 99;
    gate._id = 1;

    QThread::usleep(500);

    core->modifyGate(0,gate);
    TVGTwoPoints * simple = new TVGTwoPoints(65.0,35.0,70.0,32.0,25.0);
    core->setTVG(0,simple);
    delete simple;

    QThread::msleep(100);

    core->stopCore();
    delete core;
    delete manager;
    delete calib;
}

void CoreTest::coreTvgSetup()
{
    ModeManager * manager = generateManager();
    CalibrationManager * calib = generateCalibration();

    Core * core = new Core(manager,calib);
    core->start();

    core->getCalibrationsSnapshot();
    core->getTactTableSnapshot();

    for(int i=0; i<10; i++) {
        for(int j=0; j<8; j++) {
            TVGTwoPoints * simple = new TVGTwoPoints(8.0 * i,35.0,70.0,32.0,25.0);
            core->setTVG(j,simple);
            delete simple;
        }
        QThread::msleep(50);
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<8; j++) {
            TVGTwoPoints * simple = new TVGTwoPoints(65,35.0,70.0,8.0 * i,25.0);
            core->setTVG(j,simple);
            delete simple;
        }
        QThread::msleep(50);
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<8; j++) {
            TVGTwoPoints * simple = new TVGTwoPoints(10.0 * j,20.0 * i,20.0 * i,30.0,25.0);
            core->setTVG(j,simple);
            delete simple;
        }
        QThread::msleep(50);
    }

    QThread::msleep(200);

    core->stopCore();
    delete core;
    delete manager;
    delete calib;
}
