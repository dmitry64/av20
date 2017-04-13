#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <QObject>
#include <QTranslator>
#include <QApplication>
#include <QLibraryInfo>

enum Lang {
    LANG_ENGLISH = 0,
    LANG_RUSSIAN = 1
};

class Localization
{
    Lang _currentLanguage;
    Localization();
    QTranslator appTranslator;
    QTranslator qtTranslator;
    QString getTranslationsPath();
public:
    static Localization * getInstance()
    {
        static Localization * _instance;
        if(_instance == 0) {
            _instance = new Localization();
        }
        return _instance;
    }
    void init(QApplication &a);
    void setLanguage(Lang lang);
    QString getLanguageName(Lang lang);
    Lang getCurrentLanguage() const;
};

#endif // LOCALIZATION_H
