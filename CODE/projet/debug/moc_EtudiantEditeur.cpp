/****************************************************************************
** Meta object code from reading C++ file 'EtudiantEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EtudiantEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EtudiantEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EtudiantEditeur_t {
    QByteArrayData data[7];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EtudiantEditeur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EtudiantEditeur_t qt_meta_stringdata_EtudiantEditeur = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 14),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 13),
QT_MOC_LITERAL(4, 46, 2),
QT_MOC_LITERAL(5, 49, 5),
QT_MOC_LITERAL(6, 55, 15)
    },
    "EtudiantEditeur\0sauverEtudiant\0\0"
    "QSqlDatabase&\0db\0close\0annulerEtudiant"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EtudiantEditeur[] = {

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

void EtudiantEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EtudiantEditeur *_t = static_cast<EtudiantEditeur *>(_o);
        switch (_id) {
        case 0: _t->sauverEtudiant((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->annulerEtudiant(); break;
        default: ;
        }
    }
}

const QMetaObject EtudiantEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EtudiantEditeur.data,
      qt_meta_data_EtudiantEditeur,  qt_static_metacall, 0, 0}
};


const QMetaObject *EtudiantEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EtudiantEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EtudiantEditeur.stringdata))
        return static_cast<void*>(const_cast< EtudiantEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int EtudiantEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_EtudiantEditeurFormationPasse_t {
    QByteArrayData data[7];
    char stringdata[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EtudiantEditeurFormationPasse_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EtudiantEditeurFormationPasse_t qt_meta_stringdata_EtudiantEditeurFormationPasse = {
    {
QT_MOC_LITERAL(0, 0, 29),
QT_MOC_LITERAL(1, 30, 14),
QT_MOC_LITERAL(2, 45, 0),
QT_MOC_LITERAL(3, 46, 13),
QT_MOC_LITERAL(4, 60, 2),
QT_MOC_LITERAL(5, 63, 5),
QT_MOC_LITERAL(6, 69, 15)
    },
    "EtudiantEditeurFormationPasse\0"
    "sauverEtudiant\0\0QSqlDatabase&\0db\0close\0"
    "annulerEtudiant"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EtudiantEditeurFormationPasse[] = {

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

void EtudiantEditeurFormationPasse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EtudiantEditeurFormationPasse *_t = static_cast<EtudiantEditeurFormationPasse *>(_o);
        switch (_id) {
        case 0: _t->sauverEtudiant((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->annulerEtudiant(); break;
        default: ;
        }
    }
}

const QMetaObject EtudiantEditeurFormationPasse::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EtudiantEditeurFormationPasse.data,
      qt_meta_data_EtudiantEditeurFormationPasse,  qt_static_metacall, 0, 0}
};


const QMetaObject *EtudiantEditeurFormationPasse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EtudiantEditeurFormationPasse::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EtudiantEditeurFormationPasse.stringdata))
        return static_cast<void*>(const_cast< EtudiantEditeurFormationPasse*>(this));
    return QWidget::qt_metacast(_clname);
}

int EtudiantEditeurFormationPasse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
