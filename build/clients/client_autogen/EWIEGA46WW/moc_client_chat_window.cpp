/****************************************************************************
** Meta object code from reading C++ file 'client_chat_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/clients/client_chat_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client_chat_window.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSclient_chat_windowENDCLASS = QtMocHelpers::stringData(
    "client_chat_window",
    "clients_list",
    "",
    "my_name",
    "other_clients",
    "client_connected",
    "client_name",
    "client_name_changed",
    "old_name",
    "client_disconnected",
    "text_message_received",
    "sender",
    "message",
    "is_typing_received",
    "disconnect_from",
    "socket_disconnected",
    "send_message",
    "send_message_client",
    "send_is_typing",
    "receiver",
    "send_is_typing_client",
    "send_file",
    "file_saved",
    "path",
    "folder",
    "on_text_message_received",
    "on_is_typing_received",
    "on_init_receiving_file",
    "file_name",
    "file_size",
    "on_reject_receiving_file",
    "on_clients_list",
    "on_client_connected",
    "on_client_name_changed",
    "on_client_disconnected",
    "on_socket_disconnected"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[19];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[17];
    char stringdata6[12];
    char stringdata7[20];
    char stringdata8[9];
    char stringdata9[20];
    char stringdata10[22];
    char stringdata11[7];
    char stringdata12[8];
    char stringdata13[19];
    char stringdata14[16];
    char stringdata15[20];
    char stringdata16[13];
    char stringdata17[20];
    char stringdata18[15];
    char stringdata19[9];
    char stringdata20[22];
    char stringdata21[10];
    char stringdata22[11];
    char stringdata23[5];
    char stringdata24[7];
    char stringdata25[25];
    char stringdata26[22];
    char stringdata27[23];
    char stringdata28[10];
    char stringdata29[10];
    char stringdata30[25];
    char stringdata31[16];
    char stringdata32[20];
    char stringdata33[23];
    char stringdata34[23];
    char stringdata35[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t qt_meta_stringdata_CLASSclient_chat_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_chat_window"
        QT_MOC_LITERAL(19, 12),  // "clients_list"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 7),  // "my_name"
        QT_MOC_LITERAL(41, 13),  // "other_clients"
        QT_MOC_LITERAL(55, 16),  // "client_connected"
        QT_MOC_LITERAL(72, 11),  // "client_name"
        QT_MOC_LITERAL(84, 19),  // "client_name_changed"
        QT_MOC_LITERAL(104, 8),  // "old_name"
        QT_MOC_LITERAL(113, 19),  // "client_disconnected"
        QT_MOC_LITERAL(133, 21),  // "text_message_received"
        QT_MOC_LITERAL(155, 6),  // "sender"
        QT_MOC_LITERAL(162, 7),  // "message"
        QT_MOC_LITERAL(170, 18),  // "is_typing_received"
        QT_MOC_LITERAL(189, 15),  // "disconnect_from"
        QT_MOC_LITERAL(205, 19),  // "socket_disconnected"
        QT_MOC_LITERAL(225, 12),  // "send_message"
        QT_MOC_LITERAL(238, 19),  // "send_message_client"
        QT_MOC_LITERAL(258, 14),  // "send_is_typing"
        QT_MOC_LITERAL(273, 8),  // "receiver"
        QT_MOC_LITERAL(282, 21),  // "send_is_typing_client"
        QT_MOC_LITERAL(304, 9),  // "send_file"
        QT_MOC_LITERAL(314, 10),  // "file_saved"
        QT_MOC_LITERAL(325, 4),  // "path"
        QT_MOC_LITERAL(330, 6),  // "folder"
        QT_MOC_LITERAL(337, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(362, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(384, 22),  // "on_init_receiving_file"
        QT_MOC_LITERAL(407, 9),  // "file_name"
        QT_MOC_LITERAL(417, 9),  // "file_size"
        QT_MOC_LITERAL(427, 24),  // "on_reject_receiving_file"
        QT_MOC_LITERAL(452, 15),  // "on_clients_list"
        QT_MOC_LITERAL(468, 19),  // "on_client_connected"
        QT_MOC_LITERAL(488, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(511, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(534, 22)   // "on_socket_disconnected"
    },
    "client_chat_window",
    "clients_list",
    "",
    "my_name",
    "other_clients",
    "client_connected",
    "client_name",
    "client_name_changed",
    "old_name",
    "client_disconnected",
    "text_message_received",
    "sender",
    "message",
    "is_typing_received",
    "disconnect_from",
    "socket_disconnected",
    "send_message",
    "send_message_client",
    "send_is_typing",
    "receiver",
    "send_is_typing_client",
    "send_file",
    "file_saved",
    "path",
    "folder",
    "on_text_message_received",
    "on_is_typing_received",
    "on_init_receiving_file",
    "file_name",
    "file_size",
    "on_reject_receiving_file",
    "on_clients_list",
    "on_client_connected",
    "on_client_name_changed",
    "on_client_disconnected",
    "on_socket_disconnected"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  158,    2, 0x06,    1 /* Public */,
       5,    1,  163,    2, 0x06,    4 /* Public */,
       7,    2,  166,    2, 0x06,    6 /* Public */,
       9,    2,  171,    2, 0x06,    9 /* Public */,
      10,    2,  176,    2, 0x06,   12 /* Public */,
      13,    1,  181,    2, 0x06,   15 /* Public */,
      14,    1,  184,    2, 0x06,   17 /* Public */,
      15,    0,  187,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    0,  188,    2, 0x08,   20 /* Private */,
      17,    0,  189,    2, 0x08,   21 /* Private */,
      18,    1,  190,    2, 0x08,   22 /* Private */,
      20,    1,  193,    2, 0x08,   24 /* Private */,
      21,    0,  196,    2, 0x08,   26 /* Private */,
      22,    1,  197,    2, 0x08,   27 /* Private */,
      24,    0,  200,    2, 0x08,   29 /* Private */,
      25,    2,  201,    2, 0x08,   30 /* Private */,
      26,    1,  206,    2, 0x08,   33 /* Private */,
      27,    3,  209,    2, 0x08,   35 /* Private */,
      30,    0,  216,    2, 0x08,   39 /* Private */,
      31,    2,  217,    2, 0x08,   40 /* Private */,
      32,    1,  222,    2, 0x08,   43 /* Private */,
      33,    2,  225,    2, 0x08,   45 /* Private */,
      34,    1,  230,    2, 0x08,   48 /* Private */,
      35,    0,  233,    2, 0x08,   50 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    6,   28,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject client_chat_window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSclient_chat_windowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSclient_chat_windowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<client_chat_window, std::true_type>,
        // method 'clients_list'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        // method 'client_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'disconnect_from'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'socket_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_message_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_is_typing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_is_typing_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'folder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'on_reject_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clients_list'
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
        // method 'on_socket_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void client_chat_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_chat_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 1: _t->client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->disconnect_from((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->socket_disconnected(); break;
        case 8: _t->send_message(); break;
        case 9: _t->send_message_client(); break;
        case 10: _t->send_is_typing((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->send_is_typing_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->send_file(); break;
        case 13: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->folder(); break;
        case 15: _t->on_text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 16: _t->on_is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->on_init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 18: _t->on_reject_receiving_file(); break;
        case 19: _t->on_clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 20: _t->on_client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 22: _t->on_client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->on_socket_disconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client_chat_window::*)(QString , QStringList );
            if (_t _q_method = &client_chat_window::clients_list; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString );
            if (_t _q_method = &client_chat_window::client_connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString , QString );
            if (_t _q_method = &client_chat_window::client_name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString , QString );
            if (_t _q_method = &client_chat_window::client_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString , QString );
            if (_t _q_method = &client_chat_window::text_message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString );
            if (_t _q_method = &client_chat_window::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString );
            if (_t _q_method = &client_chat_window::disconnect_from; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)();
            if (_t _q_method = &client_chat_window::socket_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *client_chat_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client_chat_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSclient_chat_windowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int client_chat_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void client_chat_window::clients_list(QString _t1, QStringList _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void client_chat_window::client_connected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client_chat_window::client_name_changed(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void client_chat_window::client_disconnected(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void client_chat_window::text_message_received(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void client_chat_window::is_typing_received(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void client_chat_window::disconnect_from(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void client_chat_window::socket_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
