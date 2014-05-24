/****************************************************************************
** Meta object code from reading C++ file 'olam.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "olam.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'olam.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Olam_t {
    QByteArrayData data[20];
    char stringdata[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Olam_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Olam_t qt_meta_stringdata_Olam = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 16),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 9),
QT_MOC_LITERAL(4, 33, 4),
QT_MOC_LITERAL(5, 38, 24),
QT_MOC_LITERAL(6, 63, 24),
QT_MOC_LITERAL(7, 88, 15),
QT_MOC_LITERAL(8, 104, 8),
QT_MOC_LITERAL(9, 113, 3),
QT_MOC_LITERAL(10, 117, 8),
QT_MOC_LITERAL(11, 126, 23),
QT_MOC_LITERAL(12, 150, 4),
QT_MOC_LITERAL(13, 155, 25),
QT_MOC_LITERAL(14, 181, 12),
QT_MOC_LITERAL(15, 194, 4),
QT_MOC_LITERAL(16, 199, 25),
QT_MOC_LITERAL(17, 225, 26),
QT_MOC_LITERAL(18, 252, 24),
QT_MOC_LITERAL(19, 277, 28)
    },
    "Olam\0createConnection\0\0translate\0text\0"
    "on_maleng_search_clicked\0"
    "on_malmal_search_clicked\0detect_language\0"
    "printpos\0pos\0wordlist\0on_dict_word_textEdited\0"
    "arg1\0on_action_About_triggered\0"
    "searchcorpus\0word\0on_corpus_word_textEdited\0"
    "on_dict_word_returnPressed\0"
    "on_action_Exit_triggered\0"
    "on_corpus_word_returnPressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Olam[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08,
       3,    1,   80,    2, 0x08,
       5,    0,   83,    2, 0x08,
       6,    0,   84,    2, 0x08,
       7,    1,   85,    2, 0x08,
       8,    2,   88,    2, 0x08,
      11,    1,   93,    2, 0x08,
      13,    0,   96,    2, 0x08,
      14,    1,   97,    2, 0x08,
      16,    1,  100,    2, 0x08,
      17,    0,  103,    2, 0x08,
      18,    0,  104,    2, 0x08,
      19,    0,  105,    2, 0x08,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,    2,
    QMetaType::QString, QMetaType::QString, QMetaType::QStringList,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Olam::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Olam *_t = static_cast<Olam *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->createConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->translate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: _t->on_maleng_search_clicked(); break;
        case 3: _t->on_malmal_search_clicked(); break;
        case 4: { QString _r = _t->detect_language((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->printpos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->on_dict_word_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_action_About_triggered(); break;
        case 8: { QString _r = _t->searchcorpus((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: _t->on_corpus_word_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_dict_word_returnPressed(); break;
        case 11: _t->on_action_Exit_triggered(); break;
        case 12: _t->on_corpus_word_returnPressed(); break;
        default: ;
        }
    }
}

const QMetaObject Olam::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Olam.data,
      qt_meta_data_Olam,  qt_static_metacall, 0, 0}
};


const QMetaObject *Olam::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Olam::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Olam.stringdata))
        return static_cast<void*>(const_cast< Olam*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Olam::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
