#ifndef DEVICEMODE_H
#define DEVICEMODE_H

#include "tact/tacttable.h"
#include <vector>

class DeviceMode
{
    ModeTypes _type;
    std::vector<TactTable *> _tactTables;
public:
    DeviceMode();
    void setTactTables(const std::vector<TactTable *> &tactTables);
    std::vector<TactTable *> tactTables() const;
    ModeTypes type() const;
    void setType(const ModeTypes &type);
};

#endif // DEVICEMODE_H
