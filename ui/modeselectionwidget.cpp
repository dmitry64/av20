#include "modeselectionwidget.h"
#include "ui_modeselectionwidget.h"

ModeSelectionWidget::ModeSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeSelectionWidget)
{
    ui->setupUi(this);
    _core = 0;

}

ModeSelectionWidget::~ModeSelectionWidget()
{
    delete ui;
}

void ModeSelectionWidget::setCore(Core *core)
{
    _core = core;
}

void ModeSelectionWidget::init()
{
    Q_ASSERT(_core);
    ModeManager * manager = _core->getModeManager();
    std::vector<DeviceMode*> modes = manager->modes();
    for(size_t i=0; i<modes.size(); i++) {
        ModeSelectionButton * button = new ModeSelectionButton();
        connect(button,SIGNAL(modeSelected(uint8_t,uint8_t)),this,SLOT(onModeSelected(uint8_t,uint8_t)));
        button->setMode(modes.at(i),i);
        _buttons.push_back(button);
        ui->modesLayout->addWidget(button);
    }
}

void ModeSelectionWidget::onModeSelected(uint8_t mode, uint8_t scheme)
{
    emit closeWindow();
    emit modeSelected(mode,scheme);
}
