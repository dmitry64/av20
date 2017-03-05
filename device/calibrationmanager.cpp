#include "calibrationmanager.h"
#include "tvg/tvgsinglepoint.h"
#include <QDebug>

void CalibrationManager::initSearchModeCalibration()
{
    ChannelsCalibration cal1;
    cal1.setTactId(TACT_ID_SEARCH_SCHEME_1);
    CalibrationInfo info;
    info._id = 0;
    info._name = "Default calibration";
    cal1.setInfo(info);
    std::vector<Channel> channels1;
    for(int i=0; i<8; i++) {
        Channel chTemp;

        TxChannel tx;

        tx.setFreq(PulserFreq::Freq_2_5_MHz);
        tx.setProg(PulserProg::Prog_1);

        chTemp.setIndex(i);
        //TVGCurve * curve = ;
        RxChannel rx = RxChannel();
        TVGCurve * curve = new TVGSinglePoint(75.0,85.0,70.0,32.0,25.0);
        rx.setTvgCurve(curve);
        delete curve;
        //rx.setTvgCurve(curve);
        //delete curve;
        rx.setPrismTime(0);
        rx.setName("58");
        DisplayChannel dc1;
        dc1.setRx(rx);
        dc1.setTx(tx);

        std::vector<Gate> gates;
        Gate g1;
        g1._start = 100;
        g1._finish = 190;
        g1._level = 30;
        g1._id = 0;
        gates.push_back(g1);
        g1._start = 100;
        g1._finish = 190;
        g1._level = 80;
        g1._id = 1;
        gates.push_back(g1);
        g1._start = 100;
        g1._finish = 190;
        g1._level = 130;
        g1._id = 2;
        gates.push_back(g1);
        dc1.setGates(gates);
        dc1.setAngle(58);

        std::vector<DisplayChannel> dispChans;
        dispChans.push_back(dc1);
        //dispChans.push_back(dc1);
        chTemp.setDisplayChannels(dispChans);

        switch (i) {
        case 0:
            chTemp.setColor(255,30,30);
            break;
        case 1:
            chTemp.setColor(30,255,30);
            break;
        case 2:
            chTemp.setColor(255,30,255);
            break;
        case 3:
            chTemp.setColor(255,128,128);
            break;
        case 4:
            chTemp.setColor(255,255,30);
            break;
        case 5:
            chTemp.setColor(30,255,255);
            break;
        case 6:
            chTemp.setColor(128,128,255);
            break;
        case 7:
            chTemp.setColor(30,30,255);
            break;
        }

        channels1.push_back(chTemp);
    }
    cal1.setChannels(channels1);
    addCalibration(cal1);
}

/*void CalibrationManager::initHandModeCalibration()
{

}*/

CalibrationManager::CalibrationManager()
{

}

void CalibrationManager::init()
{
    initSearchModeCalibration();
}

ChannelsCalibration CalibrationManager::getLastCalibrationByTactID(TactID id)
{
    if(_calibrations.find(id) != _calibrations.end()) {
        auto list = _calibrations.at(id);
        return list.back();
    }
    else {
        Q_ASSERT(false);

    }
}

std::vector<ChannelsCalibration> CalibrationManager::getCalibrationsByTactID(TactID id)
{
    if(_calibrations.find(id) != _calibrations.end()) {
        auto list = _calibrations.at(id);

        return list;
    }
    else {
        Q_ASSERT(false);
        return std::vector<ChannelsCalibration >();
    }
}

std::vector<CalibrationInfo> CalibrationManager::getCalibrationsInfoByTactID(TactID id)
{
    if(_calibrations.find(id) != _calibrations.end()) {
        auto list = _calibrations.at(id);
        std::vector<CalibrationInfo> result;
        for(auto it = list.begin(); it!=list.end(); it++) {
            result.push_back(it.operator*().getInfo());
        }
        return result;
    }
    else {
        Q_ASSERT(false);
        return std::vector<CalibrationInfo>();
    }
}

void CalibrationManager::addCalibration(const ChannelsCalibration & calibration)
{

    uint16_t id = calibration.getTactId();
    if(_calibrations.find(id) != _calibrations.end()) {
        auto list = _calibrations.at(id);
        list.push_back(calibration);
        _calibrations[id] = list;
    }
    else {
        auto list = std::vector<ChannelsCalibration>();
        list.push_back(calibration);
        _calibrations[id] = list;
    }

}

void CalibrationManager::removeCalibration(const ChannelsCalibration & calibration)
{
    Q_ASSERT(false);
}

void CalibrationManager::applyChannelsModification(TactID id, CalibrationIndex index, ChannelID channelId, Channel channel)
{
    _calibrations[id][index].setChannel(channelId,channel);
}
