#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent), _settings(ORGANIZATION_NAME,DEVICE_NAME)
{

}

Settings::~Settings()
{
    _settings.sync();
}

void Settings::init()
{
    _settings.sync();
    logEvent("Settings","Ready");
}

void Settings::setAscanFPSEnabled(bool value)
{
    _settings.setValue("A-Scan/FPS_Enabled",value);
    emit ascanFPSEnabledChanged(value);
}

bool Settings::getAscanFPSEnabled() const
{
    return _settings.value("A-Scan/FPS_Enabled",false).toBool();
}

void Settings::setSystemSoundVolume(int value)
{
    _settings.setValue("System/Sound_Volume",value);
}

int Settings::getSystemSoundVolume() const
{
    return _settings.value("System/Sound_Volume",100).toInt();
}

void Settings::setSystemScreenBrightness(int value)
{
    _settings.setValue("System/Screen_Brightness",value);
}

int Settings::getSystemScreenBrightness() const
{
    return _settings.value("System/Screen_Brightness",100).toInt();
}

void Settings::setGlobalUiTheme(UiTheme value)
{
    _settings.setValue("Ui/Theme",static_cast<int>(value));
}

UiTheme Settings::getGlobalUiTheme() const
{
    return static_cast<UiTheme>(_settings.value("Ui/Theme",0).toInt());
}

void Settings::setCurrentOperator(QString name)
{
    _settings.setValue("Operator/Current_operator",name);
    emit operatorNameChanged(name);
}

QString Settings::getCurrentOperator()
{
    return _settings.value("Operator/Current_operator", "Unknown operator").toString();
}
