/****************************************************************************
** Meta object code from reading C++ file 'connect2py.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pc-action-detection/Pythons/connect2py.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connect2py.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Connect2Py_t {
    QByteArrayData data[12];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Connect2Py_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Connect2Py_t qt_meta_stringdata_Connect2Py = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Connect2Py"
QT_MOC_LITERAL(1, 11, 12), // "detectAction"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "action"
QT_MOC_LITERAL(4, 32, 14), // "readFromPython"
QT_MOC_LITERAL(5, 47, 16), // "setActionFileUrl"
QT_MOC_LITERAL(6, 64, 7), // "address"
QT_MOC_LITERAL(7, 72, 19), // "setPythonMainScript"
QT_MOC_LITERAL(8, 92, 6), // "script"
QT_MOC_LITERAL(9, 99, 18), // "printProcessStatus"
QT_MOC_LITERAL(10, 118, 17), // "printProcessError"
QT_MOC_LITERAL(11, 136, 18) // "printProcessOutput"

    },
    "Connect2Py\0detectAction\0\0action\0"
    "readFromPython\0setActionFileUrl\0address\0"
    "setPythonMainScript\0script\0"
    "printProcessStatus\0printProcessError\0"
    "printProcessOutput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Connect2Py[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x08 /* Private */,
      10,    0,   60,    2, 0x08 /* Private */,
      11,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Connect2Py::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Connect2Py *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->detectAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->readFromPython(); break;
        case 2: _t->setActionFileUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setPythonMainScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->printProcessStatus(); break;
        case 5: _t->printProcessError(); break;
        case 6: _t->printProcessOutput(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Connect2Py::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Connect2Py::detectAction)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Connect2Py::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Connect2Py.data,
    qt_meta_data_Connect2Py,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Connect2Py::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Connect2Py::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Connect2Py.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Connect2Py::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Connect2Py::detectAction(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
