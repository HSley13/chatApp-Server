/****************************************************************************
** Meta object code from reading C++ file 'client_main_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/clients/client_main_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client_main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSclient_main_windowENDCLASS = QtMocHelpers::stringData(
    "client_main_window",
    "connection",
    "",
    "on_connection_ACK",
    "my_name",
    "other_clients",
    "on_client_connected",
    "client_name",
    "on_client_name_changed",
    "old_name",
    "on_client_disconnected",
    "on_text_message_received",
    "sender",
    "message",
    "on_is_typing_received",
    "close_tabs",
    "index",
    "on_name_changed",
    "name"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[19];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[8];
    char stringdata5[14];
    char stringdata6[20];
    char stringdata7[12];
    char stringdata8[23];
    char stringdata9[9];
    char stringdata10[23];
    char stringdata11[25];
    char stringdata12[7];
    char stringdata13[8];
    char stringdata14[22];
    char stringdata15[11];
    char stringdata16[6];
    char stringdata17[16];
    char stringdata18[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t qt_meta_stringdata_CLASSclient_main_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_main_window"
        QT_MOC_LITERAL(19, 10),  // "connection"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 17),  // "on_connection_ACK"
        QT_MOC_LITERAL(49, 7),  // "my_name"
        QT_MOC_LITERAL(57, 13),  // "other_clients"
        QT_MOC_LITERAL(71, 19),  // "on_client_connected"
        QT_MOC_LITERAL(91, 11),  // "client_name"
        QT_MOC_LITERAL(103, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(126, 8),  // "old_name"
        QT_MOC_LITERAL(135, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(158, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(183, 6),  // "sender"
        QT_MOC_LITERAL(190, 7),  // "message"
        QT_MOC_LITERAL(198, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(220, 10),  // "close_tabs"
        QT_MOC_LITERAL(231, 5),  // "index"
        QT_MOC_LITERAL(237, 15),  // "on_name_changed"
        QT_MOC_LITERAL(253, 4)   // "name"
    },
    "client_main_window",
    "connection",
    "",
    "on_connection_ACK",
    "my_name",
    "other_clients",
    "on_client_connected",
    "client_name",
    "on_client_name_changed",
    "old_name",
    "on_client_disconnected",
    "on_text_message_received",
    "sender",
    "message",
    "on_is_typing_received",
    "close_tabs",
    "index",
    "on_name_changed",
    "name"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_main_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    2,   69,    2, 0x08,    2 /* Private */,
       6,    1,   74,    2, 0x08,    5 /* Private */,
       8,    2,   77,    2, 0x08,    7 /* Private */,
      10,    2,   82,    2, 0x08,   10 /* Private */,
      11,    2,   87,    2, 0x08,   13 /* Private */,
      14,    1,   92,    2, 0x08,   16 /* Private */,
      15,    1,   95,    2, 0x08,   18 /* Private */,
      17,    1,   98,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject client_main_window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSclient_main_windowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSclient_main_windowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<client_main_window, std::true_type>,
        // method 'connection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_connection_ACK'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        // method 'on_client_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'close_tabs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void client_main_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_main_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connection(); break;
        case 1: _t->on_connection_ACK((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 2: _t->on_client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->on_client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->on_text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->on_is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->close_tabs((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *client_main_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client_main_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSclient_main_windowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int client_main_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
