#include "olam.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QStyleFactory>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Olam");
    a.setOrganizationName("Tachyons");
    a.setOrganizationDomain("https://aboobacker.in");

    // Load Qt's own translations (standard dialogs, buttons, etc.)
    QTranslator qt_translator;
    if (qt_translator.load(QLocale::system(), "qt", "_",
                           QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&qt_translator);

    // Load app translations embedded via CONFIG += embed_translations
    QTranslator app_translator;
    if (app_translator.load(QLocale::system(), "olam", "_", ":/i18n"))
        a.installTranslator(&app_translator);

    a.setStyle(QStyleFactory::create("Fusion"));
    // Stylesheet is loaded by Olam::applyTheme() so it can switch light/dark.

    Olam w;
    w.show();
    return a.exec();
}
