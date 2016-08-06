#-------------------------------------------------
#
# Project created by QtCreator 2013-12-15T22:52:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = olam
TEMPLATE = app


SOURCES += main.cpp\
        olam.cpp \
    about.cpp

HEADERS  += olam.h \
    about.h

FORMS    += olam.ui \
    about.ui

OTHER_FILES += \
    db/olamdb.db \
    db/datuk.sqlite \
    misc/olam.desktop

RESOURCES += \
    icons.qrc

unix {
  isEmpty(PREFIX) {
    PREFIX = /usr
  }

  isEmpty(BINDIR) {
    BINDIR = $$PREFIX/bin
  }

  isEmpty(DATADIR) {
    DATADIR = $$PREFIX/share
  }
    INSTALLS += target data icon desktopfile
    target.files = $$TARGET
    target.path = $$BINDIR

    data.files = db
    data.path = $$DATADIR/olam/data


    icon.files = misc/olam.png
    icon.path = $$DATADIR/icons

    desktopfile.files = misc/olam.desktop
    desktopfile.path = $$DATADIR/applications


    QMAKE_CXXFLAGS += -DVISRULED_DATADIR=$$data.path
}
