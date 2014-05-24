/****************************************************************************
** Meta object code from reading C++ file 'about.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "about.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'about.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_About_t {
    QByteArrayData data[6];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_About_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_About_t qt_meta_stringdata_About = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 23),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 25),
QT_MOC_LITERAL(4, 57, 25),
QT_MOC_LITERAL(5, 83, 23)
    },
    "About\0on_about_button_clicked\0\0"
    "on_credits_button_clicked\0"
    "on_license_button_clicked\0"
    "on_close_button_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_About[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08,
       3,    0,   35,    2, 0x08,
       4,    0,   36,    2, 0x08,
       5,    0,   37,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void About::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        About *_t = static_cast<About *>(_o);
        switch (_id) {
        case 0: _t->on_about_button_clicked(); break;
        case 1: _t->on_credits_button_clicked(); break;
        case 2: _t->on_license_button_clicked(); break;
        case 3: _t->on_close_button_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject About::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_About.data,
      qt_meta_data_About,  qt_static_metacall, 0, 0}
};


const QMetaObject *About::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *About::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_About.stringdata))
        return static_cast<void*>(const_cast< About*>(this));
    return QDialog::qt_metacast(_clname);
}

int About::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
