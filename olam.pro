#-------------------------------------------------
#
# Project created by QtCreator 2013-12-15T22:52:19
#
#-------------------------------------------------

QT       += core gui sql texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt c++11

TARGET = olam
TEMPLATE = app


SOURCES += src/main.cpp\
        src/olam.cpp \
    src/about.cpp \
    src/olamdatabase.cpp \
    src/olamword.cpp

HEADERS  += src/olam.h \
    src/about.h \
    src/olamdatabase.h \
    src/olamword.h

FORMS    += src/olam.ui \
    src/about.ui

OTHER_FILES += \
    src/db/olamdb.db \
    src/db/datuk.sqlite \
    misc/olam.desktop

test {
    message(Configuring test build...)
    CONFIG += testcase
    TEMPLATE = app
    TARGET = olam_test
    HEADERS += test/olam_database_test.h \
      test/olam_word_test.h
    SOURCES += test/main.cpp \
      test/olam_database_test.cpp \
      test/olam_word_test.cpp \

    SOURCES -= src/main.cpp
    QT+= testlib
}

RESOURCES += \
    src/icons.qrc

linux {
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

    data.files = src/db
    data.path = $$DATADIR/olam/data


    icon.files = misc/olam.png
    icon.path = $$DATADIR/icons

    desktopfile.files = misc/olam.desktop
    desktopfile.path = $$DATADIR/applications


    QMAKE_CXXFLAGS += -DVISRULED_DATADIR=$$data.path
}

macx{
    # Add file icons into the application bundle resources
    DB.files =  src/db/olamdb.db src/db/datuk.sqlite
    DB.path = Contents/Resources
    QMAKE_BUNDLE_DATA += DB

    CONFIG += app_bundle
}

CONFIG(debug, debug|release) {
  DESTDIR = build/debug
  MOC_DIR = build/debug/.moc
  OBJECTS_DIR = build/debug/.obj
  RCC_DIR = build/debug/.rcc
  UI_DIR = build/debug/.ui
} else {
  DESTDIR = build/release
  MOC_DIR = build/release/.moc
  OBJECTS_DIR = build/release/.obj
  RCC_DIR = build/release/.rcc
  UI_DIR = build/release/.ui
}
