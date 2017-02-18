#ifndef TACTTABLE_H
#define TACTTABLE_H

#include "tact.h"
#include <vector>

class TactTable
{
    uint16_t _id;
    std::vector<Tact *> _tactTable;
public:
    TactTable();
    TactTable(TactTable * original);
    ~TactTable();
    void init();
    TactTable * getSnapshot();
    uint8_t getTactIndexByCounter(uint8_t counter) const;
    std::vector< std::pair<uint8_t, uint8_t> > getTactLines(uint8_t tactIndex);
    Tact * getTactByIndex(uint8_t index);
    uint8_t getMaxTacts() const;
    std::vector<Tact *> getTactTable() const;
    void setTactTable(const std::vector<Tact *> &tactTable);
    uint16_t getId() const;
    void setId(const uint16_t &id);
};

#endif // TACTTABLE_H
