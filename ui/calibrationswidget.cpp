#include "calibrationswidget.h"
#include "ui_calibrationswidget.h"

CalibrationsWidget::CalibrationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationsWidget)
{
    ui->setupUi(this);
    _keyboard = 0;
}

void CalibrationsWidget::init(const ChannelsCalibration & calibration)
{
    logEvent("CalibWidget","Initializing");
    Q_ASSERT(_core);

    const ModeManager * manager = _core->getModeManager();
    Q_ASSERT(manager);

    const DeviceModeIndex mode = _core->getCurrentMode();
    const SchemeIndex scheme = _core->getCurrentScheme();

    const QString modeName = manager->modes().at(mode).name();
    const QString tactName = manager->modes().at(mode).tactTables().at(scheme).getName();

    ui->modeLabel->setText(modeName);
    ui->schemeLabel->setText(tactName);

    const CalibrationsInfoList & info = _core->getAvailableCalibrationsSnapshot();

    for(auto it=_buttons.begin(); it!=_buttons.end(); it++) {
        CalibrationButton * button = it.operator*();
        Q_ASSERT(button);
        disconnect(button,SIGNAL(calibrationSelected(CalibrationIndex)),this,SLOT(onCalibrationSelected(CalibrationIndex)));
        ui->calibrationsLayout->removeWidget(button);
        delete button;
    }
    _buttons.clear();

    for(auto it=info.begin(); it!=info.end(); it++) {
        const CalibrationInfo & calibInfo = it.operator*();

        CalibrationButton * button = new CalibrationButton();
        connect(button,SIGNAL(calibrationSelected(CalibrationIndex)),this,SLOT(onCalibrationSelected(CalibrationIndex)));

        button->setCalibrationInfo(calibInfo);
        if(calibration.getInfo()._id == calibInfo._id) {
            button->setActive(true);
            button->setCurrentCalibration(true);
        }
        else {
            button->setActive(false);
            button->setCurrentCalibration(false);
        }

        ui->calibrationsLayout->addWidget(button);
        _buttons.push_back(button);
    }
    _selectedIndex = calibration.getInfo()._id;
}

void CalibrationsWidget::setCore(Core *core)
{
    Q_ASSERT(core);
    _core = core;
}

CalibrationsWidget::~CalibrationsWidget()
{
    delete ui;
}

void CalibrationsWidget::onCalibrationSelected(CalibrationIndex index)
{
    _selectedIndex = index;

    for(auto it=_buttons.begin(); it!=_buttons.end(); it++) {
        CalibrationButton * button = it.operator*();
        Q_ASSERT(button);
        if(button->info()._id == index) {
            button->setActive(true);
        }
        else {
            button->setActive(false);
        }
    }
}

void CalibrationsWidget::addCalibrationWithName(const QString &str)
{
    _core->createCalibration(0,str);
}

void CalibrationsWidget::on_newButton_released()
{
    _keyboard = new Keyboard(this);
    connect(_keyboard,SIGNAL(textReady(QString)),this,SLOT(addCalibrationWithName(QString)));
    _keyboard->show();
}

void CalibrationsWidget::on_removeButton_released()
{
    _core->removeCalibration(_selectedIndex);
}

void CalibrationsWidget::on_selectButton_2_released()
{
    _core->switchCalibration(_selectedIndex);
    emit calibrationSelected();
}
