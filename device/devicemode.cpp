#include "devicemode.h"

void DeviceMode::setTactTables(const std::vector<TactTable> &tactTables)
{
    _tactTables = tactTables;
}

std::vector<TactTable> DeviceMode::tactTables() const
{
    return _tactTables;
}

ModeTypes DeviceMode::type() const
{
    return _type;
}

void DeviceMode::setType(const ModeTypes &type)
{
    _type = type;
}

DeviceMode::DeviceMode()
{
    _type = Unknown;
}
