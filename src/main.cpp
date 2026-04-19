#include "olam.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Olam");
    a.setOrganizationName("Tachyons");
    a.setOrganizationDomain("https://aboobacker.in");

    a.setStyle(QStyleFactory::create("Fusion"));
    // Stylesheet is loaded by Olam::applyTheme() so it can switch light/dark.

    Olam w;
    w.show();
    return a.exec();
}
