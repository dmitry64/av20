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

QString DeviceMode::name() const
{
    return _name;
}

void DeviceMode::setName(const QString &name)
{
    _name = name;
}

DeviceMode::DeviceMode(): _type(ModeTypes::Unknown), _name("Unknown mode")
{
}

DeviceMode::~DeviceMode()
{
    _tactTables.clear();
}
