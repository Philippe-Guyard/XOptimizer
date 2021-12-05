/****************************************************************************
** Meta object code from reading C++ file 'xoptimizer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUI_merged/xoptimizer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xoptimizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XOptimizer_t {
    QByteArrayData data[13];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XOptimizer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XOptimizer_t qt_meta_stringdata_XOptimizer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "XOptimizer"
QT_MOC_LITERAL(1, 11, 40), // "on_DepartmentcomboBox_current..."
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 4), // "arg1"
QT_MOC_LITERAL(4, 58, 27), // "on_uploadFileButton_clicked"
QT_MOC_LITERAL(5, 86, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 108, 8), // "saveFile"
QT_MOC_LITERAL(7, 117, 4), // "name"
QT_MOC_LITERAL(8, 122, 36), // "on_CitycomboBox_2_currentText..."
QT_MOC_LITERAL(9, 159, 21), // "on_NextButton_clicked"
QT_MOC_LITERAL(10, 181, 31), // "on_stackedWidget_currentChanged"
QT_MOC_LITERAL(11, 213, 11), // "change_page"
QT_MOC_LITERAL(12, 225, 1) // "a"

    },
    "XOptimizer\0on_DepartmentcomboBox_currentTextChanged\0"
    "\0arg1\0on_uploadFileButton_clicked\0"
    "on_pushButton_clicked\0saveFile\0name\0"
    "on_CitycomboBox_2_currentTextChanged\0"
    "on_NextButton_clicked\0"
    "on_stackedWidget_currentChanged\0"
    "change_page\0a"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XOptimizer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    0,   58,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void XOptimizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XOptimizer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_DepartmentcomboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_uploadFileButton_clicked(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->saveFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_CitycomboBox_2_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_NextButton_clicked(); break;
        case 6: _t->on_stackedWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->change_page((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject XOptimizer::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_XOptimizer.data,
    qt_meta_data_XOptimizer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XOptimizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XOptimizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XOptimizer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int XOptimizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
