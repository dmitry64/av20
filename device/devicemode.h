#ifndef DEVICEMODE_H
#define DEVICEMODE_H

#include "tact/tacttable.h"
#include <vector>
#include <QString>

class DeviceMode
{
    ModeTypes _type;
    QString _name;
    std::vector<TactTable> _tactTables;
public:
    DeviceMode();
    ~DeviceMode();
    void setTactTables(const std::vector<TactTable> &tactTables);
    std::vector<TactTable> tactTables() const;
    ModeTypes type() const;
    void setType(const ModeTypes &type);
    QString name() const;
    void setName(const QString &name);
};

#endif // DEVICEMODE_H
