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
    "connection_ACK",
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
    "disconnect_from",
    "is_typing_received",
    "send_message",
    "send_message_client",
    "send_name",
    "send_file",
    "on_is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "file_saved",
    "path",
    "folder",
    "on_connection_ACK",
    "on_client_connected",
    "on_client_name_changed",
    "on_client_disconnected",
    "on_text_message_received",
    "send_is_typing",
    "receiver",
    "send_is_typing_client"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t {
    uint offsetsAndSizes[70];
    char stringdata0[19];
    char stringdata1[15];
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
    char stringdata13[16];
    char stringdata14[19];
    char stringdata15[13];
    char stringdata16[20];
    char stringdata17[10];
    char stringdata18[10];
    char stringdata19[22];
    char stringdata20[20];
    char stringdata21[10];
    char stringdata22[10];
    char stringdata23[22];
    char stringdata24[11];
    char stringdata25[5];
    char stringdata26[7];
    char stringdata27[18];
    char stringdata28[20];
    char stringdata29[23];
    char stringdata30[23];
    char stringdata31[25];
    char stringdata32[15];
    char stringdata33[9];
    char stringdata34[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_chat_windowENDCLASS_t qt_meta_stringdata_CLASSclient_chat_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "client_chat_window"
        QT_MOC_LITERAL(19, 14),  // "connection_ACK"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 7),  // "my_name"
        QT_MOC_LITERAL(43, 13),  // "other_clients"
        QT_MOC_LITERAL(57, 16),  // "client_connected"
        QT_MOC_LITERAL(74, 11),  // "client_name"
        QT_MOC_LITERAL(86, 19),  // "client_name_changed"
        QT_MOC_LITERAL(106, 8),  // "old_name"
        QT_MOC_LITERAL(115, 19),  // "client_disconnected"
        QT_MOC_LITERAL(135, 21),  // "text_message_received"
        QT_MOC_LITERAL(157, 6),  // "sender"
        QT_MOC_LITERAL(164, 7),  // "message"
        QT_MOC_LITERAL(172, 15),  // "disconnect_from"
        QT_MOC_LITERAL(188, 18),  // "is_typing_received"
        QT_MOC_LITERAL(207, 12),  // "send_message"
        QT_MOC_LITERAL(220, 19),  // "send_message_client"
        QT_MOC_LITERAL(240, 9),  // "send_name"
        QT_MOC_LITERAL(250, 9),  // "send_file"
        QT_MOC_LITERAL(260, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(282, 19),  // "init_receiving_file"
        QT_MOC_LITERAL(302, 9),  // "file_name"
        QT_MOC_LITERAL(312, 9),  // "file_size"
        QT_MOC_LITERAL(322, 21),  // "reject_receiving_file"
        QT_MOC_LITERAL(344, 10),  // "file_saved"
        QT_MOC_LITERAL(355, 4),  // "path"
        QT_MOC_LITERAL(360, 6),  // "folder"
        QT_MOC_LITERAL(367, 17),  // "on_connection_ACK"
        QT_MOC_LITERAL(385, 19),  // "on_client_connected"
        QT_MOC_LITERAL(405, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(428, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(451, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(476, 14),  // "send_is_typing"
        QT_MOC_LITERAL(491, 8),  // "receiver"
        QT_MOC_LITERAL(500, 21)   // "send_is_typing_client"
    },
    "client_chat_window",
    "connection_ACK",
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
    "disconnect_from",
    "is_typing_received",
    "send_message",
    "send_message_client",
    "send_name",
    "send_file",
    "on_is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "file_saved",
    "path",
    "folder",
    "on_connection_ACK",
    "on_client_connected",
    "on_client_name_changed",
    "on_client_disconnected",
    "on_text_message_received",
    "send_is_typing",
    "receiver",
    "send_is_typing_client"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  152,    2, 0x06,    1 /* Public */,
       5,    1,  157,    2, 0x06,    4 /* Public */,
       7,    2,  160,    2, 0x06,    6 /* Public */,
       9,    2,  165,    2, 0x06,    9 /* Public */,
      10,    2,  170,    2, 0x06,   12 /* Public */,
      13,    1,  175,    2, 0x06,   15 /* Public */,
      14,    1,  178,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  181,    2, 0x08,   19 /* Private */,
      16,    0,  182,    2, 0x08,   20 /* Private */,
      17,    0,  183,    2, 0x08,   21 /* Private */,
      18,    0,  184,    2, 0x08,   22 /* Private */,
      19,    1,  185,    2, 0x08,   23 /* Private */,
      20,    3,  188,    2, 0x08,   25 /* Private */,
      23,    0,  195,    2, 0x08,   29 /* Private */,
      24,    1,  196,    2, 0x08,   30 /* Private */,
      26,    0,  199,    2, 0x08,   32 /* Private */,
      27,    2,  200,    2, 0x08,   33 /* Private */,
      28,    1,  205,    2, 0x08,   36 /* Private */,
      29,    2,  208,    2, 0x08,   38 /* Private */,
      30,    1,  213,    2, 0x08,   41 /* Private */,
      31,    2,  216,    2, 0x08,   43 /* Private */,
      32,    1,  221,    2, 0x08,   46 /* Private */,
      34,    1,  224,    2, 0x08,   48 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    6,   21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   33,

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
        // method 'connection_ACK'
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
        // method 'disconnect_from'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_message_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_name'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
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
        // method 'on_text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_is_typing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_is_typing_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void client_chat_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_chat_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connection_ACK((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 1: _t->client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->disconnect_from((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->send_message(); break;
        case 8: _t->send_message_client(); break;
        case 9: _t->send_name(); break;
        case 10: _t->send_file(); break;
        case 11: _t->on_is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 13: _t->reject_receiving_file(); break;
        case 14: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->folder(); break;
        case 16: _t->on_connection_ACK((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 17: _t->on_client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 19: _t->on_client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->on_text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 21: _t->send_is_typing((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->send_is_typing_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client_chat_window::*)(QString , QStringList );
            if (_t _q_method = &client_chat_window::connection_ACK; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
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
            if (_t _q_method = &client_chat_window::disconnect_from; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString );
            if (_t _q_method = &client_chat_window::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void client_chat_window::connection_ACK(QString _t1, QStringList _t2)
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
void client_chat_window::disconnect_from(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void client_chat_window::is_typing_received(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
