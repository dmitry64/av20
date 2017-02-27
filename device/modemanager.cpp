#include "modemanager.h"
#include "tactid.h"
#include <QDebug>

std::vector<DeviceMode *> ModeManager::modes() const
{
    return _modes;
}

void ModeManager::addMode(DeviceMode *mode)
{
    Q_ASSERT(mode);
    _modes.push_back(mode);
}

DeviceMode *ModeManager::generateSearchMode()
{
    DeviceMode * mode = new DeviceMode();

    mode->setType(ModeTypes::SearchMode);
    std::vector<TactTable *> tactTables;

    TactTable * table1 = new TactTable();
    table1->setId(TACT_ID_SEARCH_SCHEME_1);

    std::vector<Tact*> scheme1;
    for(int i=0;i<8; i++) {
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
            tact->setRx2Enabled(false);
            tact->setTx2Enabled(false);
            tact->setTactEnabled(false);
        }

        scheme1.push_back(tact);
    }
    table1->setTactTable(scheme1);

    TactTable * table2 = new TactTable();
    table2->setId(TACT_ID_SEARCH_SCHEME_2);

    std::vector<Tact*> scheme2;
    for(int i=0;i<4; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);
        tact->setRx2(4+i);
        tact->setTx2(4+i);

        if(i<4) {
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setRx2Enabled(true);
        tact->setTx2Enabled(true);
        tact->setTactEnabled(true);
        } else {
            tact->setRx1Enabled(false);
            tact->setTx1Enabled(false);
            tact->setTactEnabled(false);
        }

        scheme2.push_back(tact);
    }
    table2->setTactTable(scheme2);

    tactTables.push_back(table1);
    tactTables.push_back(table2);

    mode->setTactTables(tactTables);

    return mode;
}

DeviceMode *ModeManager::generateHandMode()
{
    DeviceMode * mode = new DeviceMode();

    mode->setType(ModeTypes::HandMode);
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

    TactTable * table2 = new TactTable();
    table2->setId(TACT_ID_HAND_SCHEME_2);

    std::vector<Tact*> scheme2;
    for(int i=0;i<2; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);

        if(i<2) {
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setTactEnabled(true);
        } else {
            tact->setRx1Enabled(false);
            tact->setTx1Enabled(false);
            tact->setTactEnabled(false);
        }

        scheme2.push_back(tact);
    }
    table2->setTactTable(scheme2);

    tactTables.push_back(table1);
    tactTables.push_back(table2);

    mode->setTactTables(tactTables);

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
