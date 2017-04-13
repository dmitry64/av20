#include "optionswidget.h"
#include "ui_optionswidget.h"
#include "keyboards/keyboard.h"

void OptionsWidget::initOperators(System * system)
{
    ui->operatorsListWidget->clear();
    ui->operatorsListWidget->addItem("Unknown operator");

    auto names = system->getOperators()->names();

    for(auto it=names.begin(); it!=names.end(); it++) {
        ui->operatorsListWidget->addItem(it.operator*());
    }
}

void OptionsWidget::addOperatorWithName(const QString &name)
{
    if(name.compare("Unknown operator") != 0 && name.compare("") != 0) {
        System::getInstance()->getOperators()->add(name);
    }
}

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
    System * system = System::getInstance();
    Q_ASSERT(system);
    connect(system->getOperators(),SIGNAL(operatorsListChanged()),this,SLOT(onOperatorsListChanged()));
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void OptionsWidget::initColorSchemes(const Settings* settings)
{
    std::vector<QString> colorSchemes;
    colorSchemes.push_back(QString(tr("Default")));
    colorSchemes.push_back(QString(tr("Alternative")));
    ui->colorSchemeWidget->setValues(colorSchemes);
    ui->colorSchemeWidget->setIndex(static_cast<size_t>(settings->getGlobalUiTheme()));
    ui->colorSchemeWidget->setName(tr("Color scheme"));
    connect(ui->colorSchemeWidget,SIGNAL(indexChanged(size_t)),this,SLOT(onColorSchemeIndexChanged(size_t)));
}

void OptionsWidget::initLanguages()
{
    Localization * localization = Localization::getInstance();
    std::vector<QString> languages;
    languages.push_back(localization->getLanguageName(Lang::LANG_ENGLISH));
    languages.push_back(localization->getLanguageName(Lang::LANG_RUSSIAN));

    ui->languageWidget->setValues(languages);
    ui->languageWidget->setIndex(static_cast<size_t>(localization->getCurrentLanguage()));
    ui->languageWidget->setName(tr("Language"));
    connect(ui->languageWidget,SIGNAL(indexChanged(size_t)),this,SLOT(onLanguageChanged(size_t)));
}

void OptionsWidget::initBrightness(System* system)
{
    ui->brightnessWidget->setName(tr("Brightness"));
    ui->brightnessWidget->setSuffix("%");
    ui->brightnessWidget->setMax(100);
    ui->brightnessWidget->setValue(system->getBrightness());
    connect(ui->brightnessWidget,SIGNAL(valueChanged(double)),this,SLOT(onBrightnessChanged(double)));
}

void OptionsWidget::initSound(System* system)
{
    ui->soundWidget->setName(tr("Volume"));
    ui->soundWidget->setSuffix("%");
    ui->soundWidget->setMax(100);
    ui->soundWidget->setValue(system->getSoundVolume());
    connect(ui->soundWidget,SIGNAL(valueChanged(double)),this,SLOT(onSoundVolumeChanged(double)));
}

void OptionsWidget::initDebug(const Settings* settings)
{
    ui->showFps->setChecked(settings->getAscanFPSEnabled());
}

void OptionsWidget::init()
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    const Settings * settings = system->getSettings();
    Q_ASSERT(settings);

    initSound(system);
    initBrightness(system);
    initLanguages();
    initColorSchemes(settings);
    initDebug(settings);

    initOperators(system);
}

void OptionsWidget::onBrightnessChanged(double value)
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    system->setBrightness(qRound(value));
}

void OptionsWidget::onSoundVolumeChanged(double value)
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    system->setSoundVolume(qRound(value));
}

void OptionsWidget::onColorSchemeIndexChanged(size_t index)
{
    UiTheme theme = static_cast<UiTheme>(index);
    System::getInstance()->getSettings()->setGlobalUiTheme(theme);
    emit colorSchemeChanged(theme);
}

void OptionsWidget::on_showFps_toggled(bool checked)
{
    System::getInstance()->getSettings()->setAscanFPSEnabled(checked);
}

void OptionsWidget::on_selectOperatorButton_released()
{
    const QString & name = ui->operatorsListWidget->selectedItems().first()->data(0).toString();
    if(name.length()>0) {
        System::getInstance()->setCurrentOperatorName(name);
    }
}

void OptionsWidget::on_removeOperatorButton_released()
{
    const QString name = ui->operatorsListWidget->selectedItems().first()->data(0).toString();
    if(name.compare("Unknown operator") != 0) {
        System::getInstance()->getOperators()->remove(name);
    }
}

void OptionsWidget::on_addOperatorButton_released()
{
    Keyboard * keyboard = new Keyboard(this);
    connect(keyboard,SIGNAL(textReady(QString)),this,SLOT(addOperatorWithName(QString)));
    keyboard->show();
}

void OptionsWidget::onLanguageChanged(size_t index)
{
    Localization * localization = Localization::getInstance();
    Lang lang = static_cast<Lang>(index);
    logEvent("Options","Language changed to " + localization->getLanguageName(lang));

    localization->setLanguage(lang);
}

void OptionsWidget::onOperatorsListChanged()
{
    initOperators(System::getInstance());
}
