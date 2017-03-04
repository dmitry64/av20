#ifndef TACTTABLE_H
#define TACTTABLE_H

#include "tact.h"
#include <vector>

class TactTable
{
    uint16_t _id;
    std::vector<Tact> _tactTable;
public:
    TactTable();
    ~TactTable();
    void init();
    TactTable getSnapshot();
    TactIndex getTactIndexByCounter(uint8_t counter) const;
    std::vector<uint8_t> getTactLines(const uint8_t tactIndex) const;
    uint8_t getMaxTacts() const;
    uint16_t getId() const;
    void setId(const uint16_t &id);
    Tact getTactByIndex(const uint8_t index) const;
    void setTactTable(const std::vector<Tact> &tactTable);
};

#endif // TACTTABLE_H
