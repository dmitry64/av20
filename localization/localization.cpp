#include "localization.h"

Lang Localization::getCurrentLanguage() const
{
    return _currentLanguage;
}

Localization::Localization()
{

}

QString Localization::getTranslationsPath()
{
    return ":/translations/translations";
}

void Localization::init(QApplication & a)
{
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    a.installTranslator(&appTranslator);
    setLanguage(Lang::LANG_ENGLISH);
}

void Localization::setLanguage(Lang lang)
{
    switch (lang) {
    case Lang::LANG_RUSSIAN:
        appTranslator.load(getTranslationsPath() + "/translation_ru");
        break;
    case Lang::LANG_ENGLISH:
        appTranslator.load(getTranslationsPath() + "/translation_en");
        break;
    }
    _currentLanguage = lang;
}

QString Localization::getLanguageName(Lang lang)
{
    switch (lang) {
    case Lang::LANG_RUSSIAN:
        return "Русский";
    case Lang::LANG_ENGLISH:
        return "English";
    }
}
