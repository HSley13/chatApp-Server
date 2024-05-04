/****************************************************************************
** Meta object code from reading C++ file 'client_chat_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/clients/client_chat_window.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client_chat_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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
    "QHash<QString,QString>",
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
    "update_button_file",
    "text_message_sent",
    "swipe_right",
    "send_message",
    "send_is_typing",
    "send_file",
    "send_file_client",
    "folder",
    "on_init_receiving_file",
    "file_name",
    "file_size",
    "on_init_receiving_file_client",
    "on_file_saved",
    "path",
    "start_recording"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  128,    2, 0x06,    1 /* Public */,
       6,    1,  133,    2, 0x06,    4 /* Public */,
       8,    2,  136,    2, 0x06,    6 /* Public */,
      10,    1,  141,    2, 0x06,    9 /* Public */,
      11,    2,  144,    2, 0x06,   11 /* Public */,
      14,    1,  149,    2, 0x06,   14 /* Public */,
      15,    0,  152,    2, 0x06,   16 /* Public */,
      16,    0,  153,    2, 0x06,   17 /* Public */,
      17,    1,  154,    2, 0x06,   18 /* Public */,
      18,    0,  157,    2, 0x06,   20 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      19,    0,  158,    2, 0x08,   21 /* Private */,
      20,    0,  159,    2, 0x08,   22 /* Private */,
      21,    0,  160,    2, 0x08,   23 /* Private */,
      22,    0,  161,    2, 0x08,   24 /* Private */,
      23,    0,  162,    2, 0x08,   25 /* Private */,
      24,    2,  163,    2, 0x08,   26 /* Private */,
      27,    3,  168,    2, 0x08,   29 /* Private */,
      28,    1,  175,    2, 0x08,   33 /* Private */,
      30,    0,  178,    2, 0x08,   35 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   25,   26,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,   12,   25,   26,
    QMetaType::Void, QMetaType::QString,   29,
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
        QtPrivate::TypeAndForceComplete<QHash<QString,QString>, std::false_type>,
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
        // method 'update_button_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'text_message_sent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'swipe_right'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_is_typing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'folder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'on_init_receiving_file_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'on_file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'start_recording'
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
        case 0: _t->clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QHash<QString,QString>>>(_a[2]))); break;
        case 1: _t->client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->socket_disconnected(); break;
        case 7: _t->update_button_file(); break;
        case 8: _t->text_message_sent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->swipe_right(); break;
        case 10: _t->send_message(); break;
        case 11: _t->send_is_typing(); break;
        case 12: _t->send_file(); break;
        case 13: _t->send_file_client(); break;
        case 14: _t->folder(); break;
        case 15: _t->on_init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 16: _t->on_init_receiving_file_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 17: _t->on_file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->start_recording(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client_chat_window::*)(QString , QHash<QString,QString> );
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
            using _t = void (client_chat_window::*)();
            if (_t _q_method = &client_chat_window::update_button_file; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)(QString );
            if (_t _q_method = &client_chat_window::text_message_sent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (client_chat_window::*)();
            if (_t _q_method = &client_chat_window::swipe_right; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void client_chat_window::clients_list(QString _t1, QHash<QString,QString> _t2)
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
void client_chat_window::update_button_file()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void client_chat_window::text_message_sent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void client_chat_window::swipe_right()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
