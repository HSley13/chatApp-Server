/****************************************************************************
** Meta object code from reading C++ file 'client_main_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/clients/client_main_window.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
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
    "connected",
    "",
    "on_clients_list",
    "my_name",
    "QMap<QString,QString>",
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
    "on_name_changed",
    "on_item_clicked",
    "QListWidgetItem*",
    "item"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t {
    uint offsetsAndSizes[40];
    char stringdata0[19];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[8];
    char stringdata5[22];
    char stringdata6[14];
    char stringdata7[20];
    char stringdata8[12];
    char stringdata9[23];
    char stringdata10[9];
    char stringdata11[23];
    char stringdata12[25];
    char stringdata13[7];
    char stringdata14[8];
    char stringdata15[22];
    char stringdata16[16];
    char stringdata17[16];
    char stringdata18[17];
    char stringdata19[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t qt_meta_stringdata_CLASSclient_main_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_main_window"
        QT_MOC_LITERAL(19, 9),  // "connected"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 15),  // "on_clients_list"
        QT_MOC_LITERAL(46, 7),  // "my_name"
        QT_MOC_LITERAL(54, 21),  // "QMap<QString,QString>"
        QT_MOC_LITERAL(76, 13),  // "other_clients"
        QT_MOC_LITERAL(90, 19),  // "on_client_connected"
        QT_MOC_LITERAL(110, 11),  // "client_name"
        QT_MOC_LITERAL(122, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(145, 8),  // "old_name"
        QT_MOC_LITERAL(154, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(177, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(202, 6),  // "sender"
        QT_MOC_LITERAL(209, 7),  // "message"
        QT_MOC_LITERAL(217, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(239, 15),  // "on_name_changed"
        QT_MOC_LITERAL(255, 15),  // "on_item_clicked"
        QT_MOC_LITERAL(271, 16),  // "QListWidgetItem*"
        QT_MOC_LITERAL(288, 4)   // "item"
    },
    "client_main_window",
    "connected",
    "",
    "on_clients_list",
    "my_name",
    "QMap<QString,QString>",
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
    "on_name_changed",
    "on_item_clicked",
    "QListWidgetItem*",
    "item"
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
       7,    1,   74,    2, 0x08,    5 /* Private */,
       9,    2,   77,    2, 0x08,    7 /* Private */,
      11,    1,   82,    2, 0x08,   10 /* Private */,
      12,    2,   85,    2, 0x08,   12 /* Private */,
      15,    1,   90,    2, 0x08,   15 /* Private */,
      16,    0,   93,    2, 0x08,   17 /* Private */,
      17,    1,   94,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

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
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clients_list'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMap<QString,QString>, std::false_type>,
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
        // method 'on_text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_item_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>
    >,
    nullptr
} };

void client_main_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_main_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->on_clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMap<QString,QString>>>(_a[2]))); break;
        case 2: _t->on_client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->on_client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->on_is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_name_changed(); break;
        case 8: _t->on_item_clicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
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
