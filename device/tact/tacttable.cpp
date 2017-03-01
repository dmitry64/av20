#include "tacttable.h"

void TactTable::setTactTable(const std::vector<Tact *> &tactTable)
{
    _tactTable = tactTable;
}

uint16_t TactTable::getId() const
{
    return _id;
}

void TactTable::setId(const uint16_t &id)
{
    _id = id;
}

TactTable::TactTable()
{

}

TactTable::TactTable(const TactTable *original)
{
    for(size_t i=0; i<original->getTactTable().size(); i++) {
        Tact * tact = original->getTactTable().at(i);
        Tact * tactNew = new Tact(*tact);
        _tactTable.push_back(tactNew);
    }
}

TactTable::~TactTable()
{
    for(size_t i=0; i<_tactTable.size(); i++) {
        delete _tactTable.at(i);
    }
}

void TactTable::init()
{
    for(uint8_t i=0; i<MAX_TACTS_COUNT; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);

        if(i<8) {
            tact->setRx1Enabled(true);
            tact->setTx1Enabled(true);
            tact->setTactEnabled(true);
        }
        else {
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

TactIndex TactTable::getTactIndexByCounter(uint8_t counter) const
{
    uint8_t num = 0;
    for(uint8_t i=0; i<MAX_TACTS_COUNT; i++) {
        if(_tactTable[i]->getTactEnabled()) {
            if(counter == num) {
                return i;
            }
            num++;
        }
    }
    return 0;
}

std::vector< uint8_t > TactTable::getTactLines(const uint8_t tactIndex) const
{
    std::vector< uint8_t > lines;

    const Tact * tact = _tactTable.at(tactIndex);
    if(tact->getRx1Enabled()) {
        lines.push_back(0);
    }
    if(tact->getRx2Enabled()) {
        lines.push_back(1);
    }

    return lines;
}

Tact *TactTable::getTactByIndex(const uint8_t index) const
{
    return _tactTable[index];
}

uint8_t TactTable::getMaxTacts() const
{
    uint8_t num = 0;
    for(size_t i=0; i<_tactTable.size(); i++) {
        if(_tactTable[i]->getTactEnabled()) {
            num++;
        }
    }
    return num;
}
