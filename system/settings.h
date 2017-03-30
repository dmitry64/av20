#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

#include "common/commonfunctions.h"

class Settings : public QObject
{
    Q_OBJECT
    QSettings _settings;
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    void init();
public slots:
    void setAscanFPSEnabled(bool value);
    bool getAscanFPSEnabled() const;

    void setSystemSoundVolume(int value);
    int getSystemSoundVolume() const;

    void setSystemScreenBrightness(int value);
    int getSystemScreenBrightness() const;

    void setGlobalUiTheme(UiTheme value);
    UiTheme getGlobalUiTheme() const;

    void setCurrentOperator(QString name);
    QString getCurrentOperator();

signals:

    void ascanFPSEnabledChanged(bool value);
    void operatorNameChanged(QString);
public slots:
};

#endif // SETTINGS_H
