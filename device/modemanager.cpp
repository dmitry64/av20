#include "modemanager.h"
#include "tvg/tvgsinglepoint.h"

std::vector<ChannelConfiguration *> ModeManager::getConfigurations() const
{
    return _configurations;
}

ModeManager::ModeManager()
{

}

void ModeManager::init()
{
    DeviceMode * mode = new DeviceMode();
    ChannelConfiguration * channelConfiguration = new ChannelConfiguration();
    mode->setChannelConfiguration(channelConfiguration);
    for(int i=0;i<8; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        //rx->setBaseSensLevel(72 + i);
        //rx->setTvgMode(TVGMode::CurveMode);
        rx->setTvgCurve(new TVGSinglePoint(1));
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

        channelConfiguration->addChannel(chTemp);
    }

    for(int i=0;i<MAX_TACTS_COUNT; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);

        if(i<8) {
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setTactEnabled(true);
        } else {
            tact->setRx1Enabled(false);
            tact->setTx1Enabled(false);
            tact->setTactEnabled(false);
        }

        mode->addTact(tact);
    }
    _modes.push_back(mode);
}

DeviceMode *ModeManager::getDefaultMode()
{
    return _modes.at(0);
}

DeviceMode *ModeManager::getModeByModeType(ModeConfiguration mode)
{
    for(int i=0; i<_modes.size(); i++) {
        if(_modes.at(i)->getMode() == mode) {
            return _modes.at(i);
        }
    }
    return 0;
}
