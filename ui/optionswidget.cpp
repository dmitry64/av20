#include "optionswidget.h"
#include "ui_optionswidget.h"
#include "system/system.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::init()
{
    System * system = System::getInstance();

    ui->soundWidget->setName("Volume");
    ui->soundWidget->setSuffix("%");
    ui->soundWidget->setMax(100);
    ui->soundWidget->setValue(system->getSoundVolume());

    ui->brightnessWidget->setName("Brightness");
    ui->brightnessWidget->setSuffix("%");
    ui->brightnessWidget->setMax(100);
    ui->brightnessWidget->setValue(system->getBrightness());

    connect(ui->brightnessWidget,SIGNAL(valueChanged(double)),this,SLOT(onBrightnessChanged(double)));
    connect(ui->soundWidget,SIGNAL(valueChanged(double)),this,SLOT(onSoundVolumeChanged(double)));

    std::vector<QString> languages;
    languages.push_back(QString("English"));
    ui->languageWidget->setValues(languages);
    ui->languageWidget->setName("Language");

    std::vector<QString> colorSchemes;
    colorSchemes.push_back(QString("Default"));
    colorSchemes.push_back(QString("Alternative"));
    ui->colorSchemeWidget->setValues(colorSchemes);
    ui->colorSchemeWidget->setName("Color scheme");
    connect(ui->colorSchemeWidget,SIGNAL(valueChanged(QString)),this,SIGNAL(colorSchemeChanged(QString)));
}

void OptionsWidget::onBrightnessChanged(double value)
{
    System * system = System::getInstance();
    system->setBrightness(qRound(value));
}

void OptionsWidget::onSoundVolumeChanged(double value)
{
    System * system = System::getInstance();
    system->setSoundVolume(qRound(value));
}
