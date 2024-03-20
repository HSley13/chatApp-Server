/****************************************************************************
** Meta object code from reading C++ file 'server_chat_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/server/server_chat_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server_chat_window.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSserver_chat_windowENDCLASS = QtMocHelpers::stringData(
    "server_chat_window",
    "client_name_changed",
    "",
    "name",
    "is_typing",
    "send_message",
    "disconnection",
    "text_message_received",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "client_name",
    "file_name",
    "file_size",
    "file_saved",
    "path",
    "folder",
    "send_file",
    "on_client_name_changed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[19];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[10];
    char stringdata5[13];
    char stringdata6[14];
    char stringdata7[22];
    char stringdata8[8];
    char stringdata9[19];
    char stringdata10[20];
    char stringdata11[12];
    char stringdata12[10];
    char stringdata13[10];
    char stringdata14[11];
    char stringdata15[5];
    char stringdata16[7];
    char stringdata17[10];
    char stringdata18[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t qt_meta_stringdata_CLASSserver_chat_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "server_chat_window"
        QT_MOC_LITERAL(19, 19),  // "client_name_changed"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 4),  // "name"
        QT_MOC_LITERAL(45, 9),  // "is_typing"
        QT_MOC_LITERAL(55, 12),  // "send_message"
        QT_MOC_LITERAL(68, 13),  // "disconnection"
        QT_MOC_LITERAL(82, 21),  // "text_message_received"
        QT_MOC_LITERAL(104, 7),  // "message"
        QT_MOC_LITERAL(112, 18),  // "is_typing_received"
        QT_MOC_LITERAL(131, 19),  // "init_receiving_file"
        QT_MOC_LITERAL(151, 11),  // "client_name"
        QT_MOC_LITERAL(163, 9),  // "file_name"
        QT_MOC_LITERAL(173, 9),  // "file_size"
        QT_MOC_LITERAL(183, 10),  // "file_saved"
        QT_MOC_LITERAL(194, 4),  // "path"
        QT_MOC_LITERAL(199, 6),  // "folder"
        QT_MOC_LITERAL(206, 9),  // "send_file"
        QT_MOC_LITERAL(216, 22)   // "on_client_name_changed"
    },
    "server_chat_window",
    "client_name_changed",
    "",
    "name",
    "is_typing",
    "send_message",
    "disconnection",
    "text_message_received",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "client_name",
    "file_name",
    "file_size",
    "file_saved",
    "path",
    "folder",
    "send_file",
    "on_client_name_changed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSserver_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       4,    1,   83,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   86,    2, 0x08,    5 /* Private */,
       6,    0,   87,    2, 0x08,    6 /* Private */,
       7,    1,   88,    2, 0x08,    7 /* Private */,
       9,    0,   91,    2, 0x08,    9 /* Private */,
      10,    3,   92,    2, 0x08,   10 /* Private */,
      14,    1,   99,    2, 0x08,   14 /* Private */,
      16,    0,  102,    2, 0x08,   16 /* Private */,
      17,    0,  103,    2, 0x08,   17 /* Private */,
      18,    1,  104,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,   11,   12,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject server_chat_window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSserver_chat_windowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSserver_chat_windowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<server_chat_window, std::true_type>,
        // method 'client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnection'
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
        // method 'file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'folder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void server_chat_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<server_chat_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->is_typing((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->send_message(); break;
        case 3: _t->disconnection(); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->is_typing_received(); break;
        case 6: _t->init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 7: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->folder(); break;
        case 9: _t->send_file(); break;
        case 10: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (server_chat_window::*)(QString );
            if (_t _q_method = &server_chat_window::client_name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (server_chat_window::*)(QString );
            if (_t _q_method = &server_chat_window::is_typing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *server_chat_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server_chat_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSserver_chat_windowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int server_chat_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void server_chat_window::client_name_changed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void server_chat_window::is_typing(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
