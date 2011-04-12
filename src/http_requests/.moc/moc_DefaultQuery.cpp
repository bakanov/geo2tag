/****************************************************************************
** Meta object code from reading C++ file 'DefaultQuery.h'
**
** Created: Tue Apr 12 22:07:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/DefaultQuery.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DefaultQuery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DefaultQuery[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      33,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   55,   13,   13, 0x09,
      85,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DefaultQuery[] = {
    "DefaultQuery\0\0responseReceived()\0"
    "errorOccured(QString)\0reply\0"
    "process(QNetworkReply*)\0handleError()\0"
};

const QMetaObject DefaultQuery::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DefaultQuery,
      qt_meta_data_DefaultQuery, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DefaultQuery::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DefaultQuery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DefaultQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DefaultQuery))
        return static_cast<void*>(const_cast< DefaultQuery*>(this));
    return QObject::qt_metacast(_clname);
}

int DefaultQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: responseReceived(); break;
        case 1: errorOccured((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: process((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: handleError(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DefaultQuery::responseReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DefaultQuery::errorOccured(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
