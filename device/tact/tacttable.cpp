#include "tacttable.h"

void TactTable::setTactTable(const std::vector<Tact *> &tactTable)
{
    _tactTable = tactTable;
}

TactTable::TactTable()
{

}

TactTable::TactTable(TactTable *original)
{
    for(int i=0;i<original->getTactTable().size();i++) {
        Tact * tact = original->getTactTable().at(i);
        Tact * tactNew = new Tact(*tact);
        _tactTable.push_back(tactNew);
    }
}

TactTable::~TactTable()
{
    for(int i=0; i<_tactTable.size(); i++) {
        delete _tactTable.at(i);
    }
}

void TactTable::init()
{
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

        _tactTable.push_back(tact);
    }
}

TactTable *TactTable::getSnapshot()
{
    return new TactTable(this);
}


std::vector<Tact *> TactTable::getTactTable() const
{
    return _tactTable;
}

uint8_t TactTable::getTactIndexByCounter(uint8_t counter) const
{
    uint8_t num = 0;
    for(int i=0; i<MAX_TACTS_COUNT; i++) {
        if(_tactTable[i]->getTactEnabled()) {
            if(counter == num) {
                return i;
            }
            num++;
        }
    }
    return 0;
}

std::vector< std::pair<uint8_t, uint8_t> > TactTable::getTactLines(uint8_t tactIndex)
{
    std::vector< std::pair<uint8_t, uint8_t> > lines;

    Tact * tact = _tactTable.at(tactIndex);
    if(tact->getRx1Enabled()) {
        std::pair<uint8_t, uint8_t> p1(0,tact->getRx1());
        lines.push_back(p1);
    }
    if(tact->getRx2Enabled()) {
        std::pair<uint8_t, uint8_t> p2(1,tact->getRx2());
        lines.push_back(p2);
    }

    return lines;
}

Tact *TactTable::getTactByIndex(uint8_t index)
{
    return _tactTable[index];
}

uint8_t TactTable::getMaxTacts() const
{
    uint8_t num = 0;
    for(int i=0; i<_tactTable.size(); i++) {
        if(_tactTable[i]->getTactEnabled()) {
            num++;
        }
    }
    return num;
}
