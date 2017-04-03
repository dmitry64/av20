#include "modemanager.h"
#include "tactid.h"
#include <QDebug>

std::vector<DeviceMode> ModeManager::modes() const
{
    return _modes;
}

void ModeManager::addMode(DeviceMode mode)
{
    _modes.push_back(mode);
}

std::vector<Tact> ModeManager::generateSearchTacts(int tactsNumber)
{
    std::vector<Tact> scheme1;
    for(int i=0; i<8; i++) {
        Tact tact;
        tact.setRx1(i);
        tact.setTx1(i);

        if(i<tactsNumber) {
            tact.setRx1Enabled(true);
            tact.setTx1Enabled(true);
            tact.setTactEnabled(true);
        }
        else {
            tact.setRx1Enabled(false);
            tact.setTx1Enabled(false);
            tact.setTactEnabled(false);
        }

        scheme1.push_back(tact);
    }

    return scheme1;
}

TactTable ModeManager::generateSearchTable(TactID tact, int tactsNumber,const QString & name)
{
    TactTable table1;
    table1.setName(name);
    table1.setId(tact);

    const std::vector<Tact> & scheme1 = generateSearchTacts(tactsNumber);
    table1.setTactTable(scheme1);

    return table1;
}

DeviceMode ModeManager::generateSearchMode()
{
    DeviceMode mode;

    mode.setType(ModeTypes::MultiChannelMode);
    mode.setName("Search mode");
    std::vector<TactTable> tactTables;

    const TactTable & table1 = generateSearchTable(TACT_ID_SEARCH_SCHEME_1, 8, "Search scheme 1");
    const TactTable & table2 = generateSearchTable(TACT_ID_SEARCH_SCHEME_2, 8, "Search scheme 2");

    tactTables.push_back(table1);
    tactTables.push_back(table2);

    mode.setTactTables(tactTables);

    return mode;
}

DeviceMode ModeManager::generateHandMode()
{
    DeviceMode mode;

    mode.setType(ModeTypes::SingleChannelMode);
    mode.setName("Hand mode");
    std::vector<TactTable> tactTables;

    const TactTable & table1 = generateSearchTable(TACT_ID_HAND_SCHEME_1, 1, "Hand scheme 1");
    const TactTable & table2 = generateSearchTable(TACT_ID_HAND_SCHEME_2, 1, "Hand scheme 2");

    tactTables.push_back(table1);
    tactTables.push_back(table2);

    mode.setTactTables(tactTables);
    return mode;
}


ModeManager::ModeManager()
{

}

void ModeManager::init()
{
    _modes.push_back(generateSearchMode());
    _modes.push_back(generateHandMode());
}
