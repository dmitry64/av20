#include "createcalibrationmodificator.h"


CreateCalibrationModificator::CreateCalibrationModificator(const CalibrationIndex baseIndex, const QString &name) : _baseIndex(baseIndex), _name(name)
{

}

void CreateCalibrationModificator::apply(Core *core)
{
    const ChannelsCalibration & calib = core->getCalibration();
    TactID id = calib.getTactId();
    core->getCalibrationManager()->createCopyCalibration(id,_baseIndex,_name);
    core->notifyCalibration();
}
