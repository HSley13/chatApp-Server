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
    "QMap<QString,QString>",
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
    "socket_disconnected",
    "update_label",
    "QLabel*",
    "label",
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
    "on_socket_disconnected",
    "on_update_label"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t {
    uint offsetsAndSizes[80];
    char stringdata0[19];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[22];
    char stringdata5[14];
    char stringdata6[17];
    char stringdata7[12];
    char stringdata8[20];
    char stringdata9[9];
    char stringdata10[20];
    char stringdata11[22];
    char stringdata12[7];
    char stringdata13[8];
    char stringdata14[19];
    char stringdata15[20];
    char stringdata16[13];
    char stringdata17[8];
    char stringdata18[6];
    char stringdata19[13];
    char stringdata20[20];
    char stringdata21[15];
    char stringdata22[9];
    char stringdata23[22];
    char stringdata24[10];
    char stringdata25[11];
    char stringdata26[5];
    char stringdata27[7];
    char stringdata28[25];
    char stringdata29[22];
    char stringdata30[23];
    char stringdata31[10];
    char stringdata32[10];
    char stringdata33[25];
    char stringdata34[16];
    char stringdata35[20];
    char stringdata36[23];
    char stringdata37[23];
    char stringdata38[23];
    char stringdata39[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t qt_meta_stringdata_CLASSclient_chat_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_chat_window"
        QT_MOC_LITERAL(19, 12),  // "clients_list"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 7),  // "my_name"
        QT_MOC_LITERAL(41, 21),  // "QMap<QString,QString>"
        QT_MOC_LITERAL(63, 13),  // "other_clients"
        QT_MOC_LITERAL(77, 16),  // "client_connected"
        QT_MOC_LITERAL(94, 11),  // "client_name"
        QT_MOC_LITERAL(106, 19),  // "client_name_changed"
        QT_MOC_LITERAL(126, 8),  // "old_name"
        QT_MOC_LITERAL(135, 19),  // "client_disconnected"
        QT_MOC_LITERAL(155, 21),  // "text_message_received"
        QT_MOC_LITERAL(177, 6),  // "sender"
        QT_MOC_LITERAL(184, 7),  // "message"
        QT_MOC_LITERAL(192, 18),  // "is_typing_received"
        QT_MOC_LITERAL(211, 19),  // "socket_disconnected"
        QT_MOC_LITERAL(231, 12),  // "update_label"
        QT_MOC_LITERAL(244, 7),  // "QLabel*"
        QT_MOC_LITERAL(252, 5),  // "label"
        QT_MOC_LITERAL(258, 12),  // "send_message"
        QT_MOC_LITERAL(271, 19),  // "send_message_client"
        QT_MOC_LITERAL(291, 14),  // "send_is_typing"
        QT_MOC_LITERAL(306, 8),  // "receiver"
        QT_MOC_LITERAL(315, 21),  // "send_is_typing_client"
        QT_MOC_LITERAL(337, 9),  // "send_file"
        QT_MOC_LITERAL(347, 10),  // "file_saved"
        QT_MOC_LITERAL(358, 4),  // "path"
        QT_MOC_LITERAL(363, 6),  // "folder"
        QT_MOC_LITERAL(370, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(395, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(417, 22),  // "on_init_receiving_file"
        QT_MOC_LITERAL(440, 9),  // "file_name"
        QT_MOC_LITERAL(450, 9),  // "file_size"
        QT_MOC_LITERAL(460, 24),  // "on_reject_receiving_file"
        QT_MOC_LITERAL(485, 15),  // "on_clients_list"
        QT_MOC_LITERAL(501, 19),  // "on_client_connected"
        QT_MOC_LITERAL(521, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(544, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(567, 22),  // "on_socket_disconnected"
        QT_MOC_LITERAL(590, 15)   // "on_update_label"
    },
    "client_chat_window",
    "clients_list",
    "",
    "my_name",
    "QMap<QString,QString>",
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
    "socket_disconnected",
    "update_label",
    "QLabel*",
    "label",
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
    "on_socket_disconnected",
    "on_update_label"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  164,    2, 0x06,    1 /* Public */,
       6,    1,  169,    2, 0x06,    4 /* Public */,
       8,    2,  172,    2, 0x06,    6 /* Public */,
      10,    1,  177,    2, 0x06,    9 /* Public */,
      11,    2,  180,    2, 0x06,   11 /* Public */,
      14,    1,  185,    2, 0x06,   14 /* Public */,
      15,    0,  188,    2, 0x06,   16 /* Public */,
      16,    1,  189,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      19,    0,  192,    2, 0x08,   19 /* Private */,
      20,    0,  193,    2, 0x08,   20 /* Private */,
      21,    1,  194,    2, 0x08,   21 /* Private */,
      23,    1,  197,    2, 0x08,   23 /* Private */,
      24,    0,  200,    2, 0x08,   25 /* Private */,
      25,    1,  201,    2, 0x08,   26 /* Private */,
      27,    0,  204,    2, 0x08,   28 /* Private */,
      28,    2,  205,    2, 0x08,   29 /* Private */,
      29,    1,  210,    2, 0x08,   32 /* Private */,
      30,    3,  213,    2, 0x08,   34 /* Private */,
      33,    0,  220,    2, 0x08,   38 /* Private */,
      34,    2,  221,    2, 0x08,   39 /* Private */,
      35,    1,  226,    2, 0x08,   42 /* Private */,
      36,    2,  229,    2, 0x08,   44 /* Private */,
      37,    1,  234,    2, 0x08,   47 /* Private */,
      38,    0,  237,    2, 0x08,   49 /* Private */,
      39,    1,  238,    2, 0x08,   50 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    7,   31,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,

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
        QtPrivate::TypeAndForceComplete<QMap<QString,QString>, std::false_type>,
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
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'socket_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_label'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>,
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
        // method 'on_socket_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_update_label'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLabel *, std::false_type>
    >,
    nullptr
} };

void client_chat_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_chat_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMap<QString,QString>>>(_a[2]))); break;
        case 1: _t->client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->socket_disconnected(); break;
        case 7: _t->update_label((*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[1]))); break;
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
        case 19: _t->on_clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMap<QString,QString>>>(_a[2]))); break;
        case 20: _t->on_client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 22: _t->on_client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->on_socket_disconnected(); break;
        case 24: _t->on_update_label((*reinterpret_cast< std::add_pointer_t<QLabel*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client_chat_window::*)(QString , QMap<QString,QString> );
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
            using _t = void (client_chat_window::*)(QString );
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
            using _t = void (client_chat_window::*)();
            if (_t _q_method = &client_chat_window::socket_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QLabel * );
            if (_t _q_method = &client_chat_window::update_label; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
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
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void client_chat_window::clients_list(QString _t1, QMap<QString,QString> _t2)
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
void client_chat_window::client_disconnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
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
void client_chat_window::socket_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void client_chat_window::update_label(QLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
