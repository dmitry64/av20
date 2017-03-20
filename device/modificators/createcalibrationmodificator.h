#ifndef CREATECALIBRATIONMODIFICATOR_H
#define CREATECALIBRATIONMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class CreateCalibrationModificator : public Modificator
{
    CalibrationIndex _baseIndex;
    QString _name;
public:
    CreateCalibrationModificator(const CalibrationIndex baseIndex,const QString & name);
    void apply(Core * core);
};

#endif // CREATECALIBRATIONMODIFICATOR_H
