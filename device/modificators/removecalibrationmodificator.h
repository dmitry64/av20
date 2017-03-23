#ifndef REMOVECALIBRATIONMODIFICATOR_H
#define REMOVECALIBRATIONMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class RemoveCalibrationModificator : public Modificator
{
    CalibrationIndex _index;
public:
    explicit RemoveCalibrationModificator(const CalibrationIndex index);
    void apply(Core * core);
};

#endif // REMOVECALIBRATIONMODIFICATOR_H
