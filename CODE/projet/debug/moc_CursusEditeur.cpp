/****************************************************************************
** Meta object code from reading C++ file 'CursusEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CursusEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CursusEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CursusEditeurNew_t {
    QByteArrayData data[8];
    char stringdata[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CursusEditeurNew_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CursusEditeurNew_t qt_meta_stringdata_CursusEditeurNew = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 12),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 13),
QT_MOC_LITERAL(4, 45, 2),
QT_MOC_LITERAL(5, 48, 5),
QT_MOC_LITERAL(6, 54, 13),
QT_MOC_LITERAL(7, 68, 16)
    },
    "CursusEditeurNew\0sauverCursus\0\0"
    "QSqlDatabase&\0db\0close\0annulerCursus\0"
    "setUVObligatoire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CursusEditeurNew[] = {

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
       1,    1,   34,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    1,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void CursusEditeurNew::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CursusEditeurNew *_t = static_cast<CursusEditeurNew *>(_o);
        switch (_id) {
        case 0: _t->sauverCursus((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->annulerCursus(); break;
        case 3: _t->setUVObligatoire((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CursusEditeurNew::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CursusEditeurNew.data,
      qt_meta_data_CursusEditeurNew,  qt_static_metacall, 0, 0}
};


const QMetaObject *CursusEditeurNew::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CursusEditeurNew::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CursusEditeurNew.stringdata))
        return static_cast<void*>(const_cast< CursusEditeurNew*>(this));
    return QWidget::qt_metacast(_clname);
}

int CursusEditeurNew::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
