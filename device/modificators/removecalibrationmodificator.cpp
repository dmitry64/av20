#include "removecalibrationmodificator.h"

RemoveCalibrationModificator::RemoveCalibrationModificator(const CalibrationIndex index) : _index(index)
{

}

void RemoveCalibrationModificator::apply(Core *core)
{
    const ChannelsCalibration & calib = core->getCalibration();
    TactID id = calib.getTactId();
    core->getCalibrationManager()->removeCalibration(id,_index);
    core->notifyCalibration();
}
