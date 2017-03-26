#ifndef TACTTABLE_H
#define TACTTABLE_H

#include "tact.h"
#include <vector>
#include <QString>

class TactTable
{
    TactID _id;
    QString _name;
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
    std::vector<Tact> getTactTable() const;
    QString getName() const;
    void setName(const QString &name);
};

#endif // TACTTABLE_H
