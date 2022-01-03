/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../test_tcp/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "connect_btn_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "connect_to_dev"
QT_MOC_LITERAL(4, 47, 19), // "disconnect_from_dev"
QT_MOC_LITERAL(5, 67, 9), // "read_regs"
QT_MOC_LITERAL(6, 77, 9), // "write_reg"
QT_MOC_LITERAL(7, 87, 21), // "response_to_read_regs"
QT_MOC_LITERAL(8, 109, 6), // "status"
QT_MOC_LITERAL(9, 116, 21), // "response_to_write_reg"
QT_MOC_LITERAL(10, 138, 13), // "process_error"
QT_MOC_LITERAL(11, 152, 20), // "QModBus::ModBusError"
QT_MOC_LITERAL(12, 173, 5), // "error"
QT_MOC_LITERAL(13, 179, 13), // "change_status"
QT_MOC_LITERAL(14, 193, 23), // "device02_connect_to_dev"
QT_MOC_LITERAL(15, 217, 28), // "device02_disconnect_from_dev"
QT_MOC_LITERAL(16, 246, 18), // "device02_read_regs"
QT_MOC_LITERAL(17, 265, 30), // "device02_response_to_read_regs"
QT_MOC_LITERAL(18, 296, 22), // "device02_process_error"
QT_MOC_LITERAL(19, 319, 22), // "device02_change_status"
QT_MOC_LITERAL(20, 342, 20), // "device01_dialog_exec"
QT_MOC_LITERAL(21, 363, 20), // "device02_dialog_exec"
QT_MOC_LITERAL(22, 384, 8) // "readData"

    },
    "MainWindow\0connect_btn_clicked\0\0"
    "connect_to_dev\0disconnect_from_dev\0"
    "read_regs\0write_reg\0response_to_read_regs\0"
    "status\0response_to_write_reg\0process_error\0"
    "QModBus::ModBusError\0error\0change_status\0"
    "device02_connect_to_dev\0"
    "device02_disconnect_from_dev\0"
    "device02_read_regs\0device02_response_to_read_regs\0"
    "device02_process_error\0device02_change_status\0"
    "device01_dialog_exec\0device02_dialog_exec\0"
    "readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    1,  109,    2, 0x0a /* Public */,
       9,    1,  112,    2, 0x0a /* Public */,
      10,    1,  115,    2, 0x0a /* Public */,
      13,    0,  118,    2, 0x0a /* Public */,
      14,    0,  119,    2, 0x0a /* Public */,
      15,    0,  120,    2, 0x0a /* Public */,
      16,    0,  121,    2, 0x0a /* Public */,
      17,    1,  122,    2, 0x0a /* Public */,
      18,    1,  125,    2, 0x0a /* Public */,
      19,    0,  128,    2, 0x0a /* Public */,
      20,    0,  129,    2, 0x0a /* Public */,
      21,    0,  130,    2, 0x0a /* Public */,
      22,    0,  131,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connect_btn_clicked(); break;
        case 1: _t->connect_to_dev(); break;
        case 2: _t->disconnect_from_dev(); break;
        case 3: _t->read_regs(); break;
        case 4: _t->write_reg(); break;
        case 5: _t->response_to_read_regs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->response_to_write_reg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->process_error((*reinterpret_cast< QModBus::ModBusError(*)>(_a[1]))); break;
        case 8: _t->change_status(); break;
        case 9: _t->device02_connect_to_dev(); break;
        case 10: _t->device02_disconnect_from_dev(); break;
        case 11: _t->device02_read_regs(); break;
        case 12: _t->device02_response_to_read_regs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->device02_process_error((*reinterpret_cast< QModBus::ModBusError(*)>(_a[1]))); break;
        case 14: _t->device02_change_status(); break;
        case 15: _t->device01_dialog_exec(); break;
        case 16: _t->device02_dialog_exec(); break;
        case 17: _t->readData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QModBus::ModBusError >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QModBus::ModBusError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
