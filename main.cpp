#include "olam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Olam w;
    w.show();
    
    return a.exec();
}
