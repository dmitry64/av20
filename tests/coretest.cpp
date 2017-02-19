#include "coretest.h"
#include "device/tvg/tvgsinglepoint.h"

QTEST_MAIN(CoreTest)

ModeManager *CoreTest::generateManager()
{
    DeviceMode * mode = new DeviceMode();

    mode->setType(ModeTypes::SearchMode);
    std::vector<TactTable *> tactTables;

    TactTable * table1 = new TactTable();
    table1->setId(TACT_ID_HAND_SCHEME_1);

    std::vector<Tact*> scheme1;
    for(int i=0;i<3; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);

        if(i<3) {
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setTactEnabled(true);
        } else {
            tact->setRx1Enabled(false);
            tact->setTx1Enabled(false);
            tact->setTactEnabled(false);
        }

        scheme1.push_back(tact);
    }
    table1->setTactTable(scheme1);
    table1->setId(TACT_ID_SEARCH_SCHEME_1);
    tactTables.push_back(table1);


    mode->setTactTables(tactTables);
    mode->setType(ModeTypes::SearchMode);


    ModeManager * manager = new ModeManager();
    manager->addMode(mode);
    return manager;
}

CalibrationManager *CoreTest::generateCalibration()
{
    CalibrationManager * calibrationManager = new CalibrationManager();
    ChannelsCalibration * calib = new ChannelsCalibration();
    calib->setTactId(TACT_ID_SEARCH_SCHEME_1);
    std::vector<Channel *> channels1;
    for(int i=0;i<8; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_10_0_MHz);
        tx->setProg(PulserProg::Prog_6);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(0.9,0.9));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 10;
        g1._finish = 12;
        g1._level = 5;
        g1._id = 0;
        gates.push_back(g1);
        rx->setGates(gates);

        switch (i) {
            case 0:
            chTemp->setColor(255,30,30);
            break;
            case 1:
            chTemp->setColor(30,255,30);
            break;
            case 2:
            chTemp->setColor(255,30,255);
            break;
            case 3:
            chTemp->setColor(255,128,128);
            break;
            case 4:
            chTemp->setColor(255,255,30);
            break;
            case 5:
            chTemp->setColor(30,255,255);
            break;
            case 6:
            chTemp->setColor(128,128,255);
            break;
            case 7:
            chTemp->setColor(30,30,255);
            break;
        }

        rx->setName("58");

        channels1.push_back(chTemp);
    }
    calib->setChannels(channels1);
    calibrationManager->addCalibration(calib);
    return calibrationManager;
}

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
    TVGSinglePoint * simple = new TVGSinglePoint(0.999,0.999);
    core->setTVG(0,simple);
    delete simple;


    core->stopCore();
    delete core;
    delete manager;
    delete calib;
}
