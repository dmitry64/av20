#include "modeselectionbutton.h"
#include "ui_modeselectionbutton.h"
#include <QPushButton>

ModeSelectionButton::ModeSelectionButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeSelectionButton)
{
    ui->setupUi(this);
}

ModeSelectionButton::~ModeSelectionButton()
{
    delete ui;
}

void ModeSelectionButton::setMode(DeviceMode mode, uint8_t index)
{
    _mode = mode;
    _index = index;
    QString name = "none";

    switch (mode.type()) {
    case ModeTypes::MultiChannelMode:
        name = "Search modes:";
        break;
    case ModeTypes::SingleChannelMode:
        name = "Hand modes:";
        break;
    case ModeTypes::HeadMode:
        name = "Head scanner modes:";
        break;
    case ModeTypes::WheelMode:
        name = "Wheel modes:";
        break;
    case ModeTypes::Unknown:
        name = "Unknown";
        break;
    }

    ui->submodesBox->setTitle(name);
    const std::vector<TactTable> &tactTables = mode.tactTables();
    for(size_t i=0; i<tactTables.size(); i++) {
        const TactTable & tactTable = tactTables.at(i);
        SchemeSelectionButton * button = new SchemeSelectionButton();
        button->setText(tactTable.getName());
        button->setIndex(i);
        button->setMinimumSize(QSize(48,48));
        connect(button,SIGNAL(schemeSelected(uint8_t)),this,SLOT(onSchemeSelected(uint8_t)));
        ui->submodeLayout->addWidget(button);
    }
}

void ModeSelectionButton::onSchemeSelected(uint8_t index)
{
    emit modeSelected(_index,index);
}
