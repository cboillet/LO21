/****************************************************************************
** Meta object code from reading C++ file 'UVEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../CODE/projet/UVEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UVEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UVEditeurNew_t {
    QByteArrayData data[7];
    char stringdata[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UVEditeurNew_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UVEditeurNew_t qt_meta_stringdata_UVEditeurNew = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 8),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 13),
QT_MOC_LITERAL(4, 37, 2),
QT_MOC_LITERAL(5, 40, 5),
QT_MOC_LITERAL(6, 46, 9)
    },
    "UVEditeurNew\0sauverUV\0\0QSqlDatabase&\0"
    "db\0close\0annulerUV"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVEditeurNew[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    0,   32,    2, 0x0a /* Public */,
       6,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UVEditeurNew::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UVEditeurNew *_t = static_cast<UVEditeurNew *>(_o);
        switch (_id) {
        case 0: _t->sauverUV((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->annulerUV(); break;
        default: ;
        }
    }
}

const QMetaObject UVEditeurNew::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVEditeurNew.data,
      qt_meta_data_UVEditeurNew,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVEditeurNew::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVEditeurNew::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVEditeurNew.stringdata))
        return static_cast<void*>(const_cast< UVEditeurNew*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVEditeurNew::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_UVEditeur_t {
    QByteArrayData data[1];
    char stringdata[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UVEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UVEditeur_t qt_meta_stringdata_UVEditeur = {
    {
QT_MOC_LITERAL(0, 0, 9)
    },
    "UVEditeur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UVEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void UVEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject UVEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UVEditeur.data,
      qt_meta_data_UVEditeur,  qt_static_metacall, 0, 0}
};


const QMetaObject *UVEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UVEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UVEditeur.stringdata))
        return static_cast<void*>(const_cast< UVEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int UVEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
