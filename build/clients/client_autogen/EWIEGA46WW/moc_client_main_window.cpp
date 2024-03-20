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
    "send_message",
    "send_name",
    "send_file",
    "text_message_received",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "client_name",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "file_saved",
    "path",
    "folder"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[19];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[10];
    char stringdata5[10];
    char stringdata6[22];
    char stringdata7[8];
    char stringdata8[19];
    char stringdata9[20];
    char stringdata10[12];
    char stringdata11[10];
    char stringdata12[10];
    char stringdata13[22];
    char stringdata14[11];
    char stringdata15[5];
    char stringdata16[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_main_windowENDCLASS_t qt_meta_stringdata_CLASSclient_main_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_main_window"
        QT_MOC_LITERAL(19, 10),  // "connection"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 12),  // "send_message"
        QT_MOC_LITERAL(44, 9),  // "send_name"
        QT_MOC_LITERAL(54, 9),  // "send_file"
        QT_MOC_LITERAL(64, 21),  // "text_message_received"
        QT_MOC_LITERAL(86, 7),  // "message"
        QT_MOC_LITERAL(94, 18),  // "is_typing_received"
        QT_MOC_LITERAL(113, 19),  // "init_receiving_file"
        QT_MOC_LITERAL(133, 11),  // "client_name"
        QT_MOC_LITERAL(145, 9),  // "file_name"
        QT_MOC_LITERAL(155, 9),  // "file_size"
        QT_MOC_LITERAL(165, 21),  // "reject_receiving_file"
        QT_MOC_LITERAL(187, 10),  // "file_saved"
        QT_MOC_LITERAL(198, 4),  // "path"
        QT_MOC_LITERAL(203, 6)   // "folder"
    },
    "client_main_window",
    "connection",
    "",
    "send_message",
    "send_name",
    "send_file",
    "text_message_received",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "client_name",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "file_saved",
    "path",
    "folder"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_main_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    0,   76,    2, 0x08,    3 /* Private */,
       5,    0,   77,    2, 0x08,    4 /* Private */,
       6,    1,   78,    2, 0x08,    5 /* Private */,
       8,    0,   81,    2, 0x08,    7 /* Private */,
       9,    3,   82,    2, 0x08,    8 /* Private */,
      13,    0,   89,    2, 0x08,   12 /* Private */,
      14,    1,   90,    2, 0x08,   13 /* Private */,
      16,    0,   93,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,

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
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_name'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'reject_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'folder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
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
        case 1: _t->send_message(); break;
        case 2: _t->send_name(); break;
        case 3: _t->send_file(); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->is_typing_received(); break;
        case 6: _t->init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 7: _t->reject_receiving_file(); break;
        case 8: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->folder(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
