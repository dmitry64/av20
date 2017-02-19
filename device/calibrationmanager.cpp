#include "calibrationmanager.h"
#include "tvg/tvgsinglepoint.h"
#include <QDebug>

void CalibrationManager::initSearchModeCalibration()
{
    ChannelsCalibration * cal1 = new ChannelsCalibration();
    cal1->setTactId(TACT_ID_SEARCH_SCHEME_1);
    std::vector<Channel *> channels1;
    for(int i=0;i<8; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(0.5,0.5));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
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
    cal1->setChannels(channels1);
    addCalibration(cal1);

    ChannelsCalibration * cal2 = new ChannelsCalibration();
    cal2->setTactId(TACT_ID_SEARCH_SCHEME_2);
    std::vector<Channel *> channels2;
    for(int i=0;i<8; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(0.5,0.5));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
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

        rx->setName("0");

        channels2.push_back(chTemp);
    }
    cal2->setChannels(channels2);
    addCalibration(cal2);
}

void CalibrationManager::initHandModeCalibration()
{
    ChannelsCalibration * cal1 = new ChannelsCalibration();
    cal1->setTactId(TACT_ID_HAND_SCHEME_1);
    std::vector<Channel *> channels1;
    for(int i=0;i<3; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(0.5,0.5));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
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

        rx->setName("70");

        channels1.push_back(chTemp);
    }
    cal1->setChannels(channels1);
    addCalibration(cal1);

    ChannelsCalibration * cal2 = new ChannelsCalibration();
    cal2->setTactId(TACT_ID_HAND_SCHEME_2);
    std::vector<Channel *> channels2;
    for(int i=0;i<2; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(0.5,0.5));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
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

        rx->setName("42");

        channels2.push_back(chTemp);
    }
    cal2->setChannels(channels2);
    addCalibration(cal2);
}

CalibrationManager::CalibrationManager()
{

}

void CalibrationManager::init()
{
    initSearchModeCalibration();
    initHandModeCalibration();
}

ChannelsCalibration *CalibrationManager::getLastCalibrationByTactID(uint16_t id)
{
    if(_calibrations.find(id) != _calibrations.end()) {
        auto list = _calibrations.at(id);
        return list->back();
    } else {
        Q_ASSERT(false);
        return 0;
    }
}

std::vector<ChannelsCalibration *> CalibrationManager::getCalibrationsByTactID(uint16_t id)
{
    Q_ASSERT(false);
}

void CalibrationManager::addCalibration(ChannelsCalibration *calibration)
{
    std::list<ChannelsCalibration*> * list = 0;
    uint16_t id = calibration->getTactId();
    if(_calibrations.find(id) != _calibrations.end()) {
        list = _calibrations.at(id);
    } else {
        list = new std::list<ChannelsCalibration*>();
        _calibrations[id] = list;
    }
    list->push_back(calibration);
}

void CalibrationManager::removeCalibration(ChannelsCalibration *calibration)
{
    Q_ASSERT(false);
}

