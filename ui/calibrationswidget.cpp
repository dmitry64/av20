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

    ModeManager * manager = _core->getModeManager();

    DeviceModeIndex mode = _core->getCurrentMode();
    SchemeIndex scheme = _core->getCurrentScheme();

    ModeTypes modeType = manager->modes().at(mode)->type();
    TactID tactid = manager->modes().at(mode)->tactTables().at(scheme)->getId();

    ui->modeLabel->setText(QString::number(modeType));
    ui->schemeLabel->setText(QString::number(tactid));

    CalibrationsInfoList info =  _core->getAvailableCalibrationsSnapshot();

    for(size_t i=0; i<_buttons.size(); i++) {
        CalibrationButton * button = _buttons.at(i);
        disconnect(button,SIGNAL(calibrationSelected(CalibrationIndex)),this,SLOT(onCalibrationSelected(CalibrationIndex)));
        ui->calibrationsLayout->removeWidget(button);
        delete button;
    }
    _buttons.clear();

    for(size_t i=0; i<info.size(); i++) {
        CalibrationButton * button = new CalibrationButton();
        connect(button,SIGNAL(calibrationSelected(CalibrationIndex)),this,SLOT(onCalibrationSelected(CalibrationIndex)));
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

void CalibrationsWidget::onCalibrationSelected(CalibrationIndex index)
{

}

void CalibrationsWidget::on_newButton_released()
{

}

void CalibrationsWidget::on_removeButton_released()
{

}

void CalibrationsWidget::on_selectButton_2_released()
{

}
