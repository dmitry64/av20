#include "calibrationswidget.h"
#include "ui_calibrationswidget.h"

CalibrationsWidget::CalibrationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationsWidget)
{
    ui->setupUi(this);
}

void CalibrationsWidget::init(ChannelsCalibration * calibration)
{
    Q_ASSERT(_core);

    CalibrationsInfoList info =  _core->getAvailableCalibrationsSnapshot();

    for(size_t i=0; i<info.size(); i++) {
        CalibrationButton * button = new CalibrationButton();
        CalibrationInfo calibInfo = info.at(i);
        button->setCalibrationInfo(calibInfo);
        if(calibration->getInfo()._id == calibInfo._id) {
            button->setActive(true);
        } else {
            button->setActive(false);
        }

        ui->calibrationsLayout->addWidget(button);
        _buttons.push_back(button);
    }

}

void CalibrationsWidget::setCore(Core *core)
{
    _core = core;
}

CalibrationsWidget::~CalibrationsWidget()
{
    delete ui;
}
