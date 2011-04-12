/****************************************************************************
** Meta object code from reading C++ file 'LoginQuery.h'
**
** Created: Tue Apr 12 22:07:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/LoginQuery.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginQuery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginQuery[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   24,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoginQuery[] = {
    "LoginQuery\0\0connected()\0reply\0"
    "processReply(QNetworkReply*)\0"
};

const QMetaObject LoginQuery::staticMetaObject = {
    { &DefaultQuery::staticMetaObject, qt_meta_stringdata_LoginQuery,
      qt_meta_data_LoginQuery, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginQuery::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginQuery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginQuery))
        return static_cast<void*>(const_cast< LoginQuery*>(this));
    return DefaultQuery::qt_metacast(_clname);
}

int LoginQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DefaultQuery::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connected(); break;
        case 1: processReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoginQuery::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
