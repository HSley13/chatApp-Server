/****************************************************************************
** Meta object code from reading C++ file 'client_manager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/clients/client_manager.h"
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
#error "The header file 'client_manager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSclient_managerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSclient_managerENDCLASS = QtMocHelpers::stringData(
    "client_manager",
    "text_message_received",
    "",
    "sender",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "init_receiving_file_client",
    "reject_receiving_file_client",
    "file_saved",
    "path",
    "client_connected",
    "client_name",
    "clients_list",
    "my_name",
    "QMap<QString,QString>",
    "other_clients",
    "client_name_changed",
    "old_name",
    "client_disconnected",
    "socket_disconnected",
    "on_disconnected",
    "on_ready_read",
    "file_connect",
    "on_new_connection"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSclient_managerENDCLASS_t {
    uint offsetsAndSizes[56];
    char stringdata0[15];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[8];
    char stringdata5[19];
    char stringdata6[20];
    char stringdata7[10];
    char stringdata8[10];
    char stringdata9[22];
    char stringdata10[27];
    char stringdata11[29];
    char stringdata12[11];
    char stringdata13[5];
    char stringdata14[17];
    char stringdata15[12];
    char stringdata16[13];
    char stringdata17[8];
    char stringdata18[22];
    char stringdata19[14];
    char stringdata20[20];
    char stringdata21[9];
    char stringdata22[20];
    char stringdata23[20];
    char stringdata24[16];
    char stringdata25[14];
    char stringdata26[13];
    char stringdata27[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSclient_managerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSclient_managerENDCLASS_t qt_meta_stringdata_CLASSclient_managerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "client_manager"
        QT_MOC_LITERAL(15, 21),  // "text_message_received"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 6),  // "sender"
        QT_MOC_LITERAL(45, 7),  // "message"
        QT_MOC_LITERAL(53, 18),  // "is_typing_received"
        QT_MOC_LITERAL(72, 19),  // "init_receiving_file"
        QT_MOC_LITERAL(92, 9),  // "file_name"
        QT_MOC_LITERAL(102, 9),  // "file_size"
        QT_MOC_LITERAL(112, 21),  // "reject_receiving_file"
        QT_MOC_LITERAL(134, 26),  // "init_receiving_file_client"
        QT_MOC_LITERAL(161, 28),  // "reject_receiving_file_client"
        QT_MOC_LITERAL(190, 10),  // "file_saved"
        QT_MOC_LITERAL(201, 4),  // "path"
        QT_MOC_LITERAL(206, 16),  // "client_connected"
        QT_MOC_LITERAL(223, 11),  // "client_name"
        QT_MOC_LITERAL(235, 12),  // "clients_list"
        QT_MOC_LITERAL(248, 7),  // "my_name"
        QT_MOC_LITERAL(256, 21),  // "QMap<QString,QString>"
        QT_MOC_LITERAL(278, 13),  // "other_clients"
        QT_MOC_LITERAL(292, 19),  // "client_name_changed"
        QT_MOC_LITERAL(312, 8),  // "old_name"
        QT_MOC_LITERAL(321, 19),  // "client_disconnected"
        QT_MOC_LITERAL(341, 19),  // "socket_disconnected"
        QT_MOC_LITERAL(361, 15),  // "on_disconnected"
        QT_MOC_LITERAL(377, 13),  // "on_ready_read"
        QT_MOC_LITERAL(391, 12),  // "file_connect"
        QT_MOC_LITERAL(404, 17)   // "on_new_connection"
    },
    "client_manager",
    "text_message_received",
    "",
    "sender",
    "message",
    "is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "reject_receiving_file",
    "init_receiving_file_client",
    "reject_receiving_file_client",
    "file_saved",
    "path",
    "client_connected",
    "client_name",
    "clients_list",
    "my_name",
    "QMap<QString,QString>",
    "other_clients",
    "client_name_changed",
    "old_name",
    "client_disconnected",
    "socket_disconnected",
    "on_disconnected",
    "on_ready_read",
    "file_connect",
    "on_new_connection"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSclient_managerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  110,    2, 0x06,    1 /* Public */,
       5,    1,  115,    2, 0x06,    4 /* Public */,
       6,    2,  118,    2, 0x06,    6 /* Public */,
       9,    0,  123,    2, 0x06,    9 /* Public */,
      10,    3,  124,    2, 0x06,   10 /* Public */,
      11,    1,  131,    2, 0x06,   14 /* Public */,
      12,    1,  134,    2, 0x06,   16 /* Public */,
      14,    1,  137,    2, 0x06,   18 /* Public */,
      16,    2,  140,    2, 0x06,   20 /* Public */,
      20,    2,  145,    2, 0x06,   23 /* Public */,
      22,    1,  150,    2, 0x06,   26 /* Public */,
      23,    0,  153,    2, 0x06,   28 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      24,    0,  154,    2, 0x08,   29 /* Private */,
      25,    0,  155,    2, 0x08,   30 /* Private */,
      26,    0,  156,    2, 0x08,   31 /* Private */,
      27,    0,  157,    2, 0x08,   32 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    3,    7,    8,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 18,   17,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject client_manager::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSclient_managerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSclient_managerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSclient_managerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<client_manager, std::true_type>,
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'reject_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'init_receiving_file_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'reject_receiving_file_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'client_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'clients_list'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMap<QString,QString>, std::false_type>,
        // method 'client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'socket_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ready_read'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'file_connect'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_new_connection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void client_manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<client_manager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 3: _t->reject_receiving_file(); break;
        case 4: _t->init_receiving_file_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 5: _t->reject_receiving_file_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->client_connected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->clients_list((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMap<QString,QString>>>(_a[2]))); break;
        case 9: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->client_disconnected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->socket_disconnected(); break;
        case 12: _t->on_disconnected(); break;
        case 13: _t->on_ready_read(); break;
        case 14: _t->file_connect(); break;
        case 15: _t->on_new_connection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client_manager::*)(QString , QString );
            if (_t _q_method = &client_manager::text_message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString );
            if (_t _q_method = &client_manager::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString , qint64 );
            if (_t _q_method = &client_manager::init_receiving_file; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (client_manager::*)();
            if (_t _q_method = &client_manager::reject_receiving_file; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString , QString , qint64 );
            if (_t _q_method = &client_manager::init_receiving_file_client; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString );
            if (_t _q_method = &client_manager::reject_receiving_file_client; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString );
            if (_t _q_method = &client_manager::file_saved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString );
            if (_t _q_method = &client_manager::client_connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString , QMap<QString,QString> );
            if (_t _q_method = &client_manager::clients_list; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString , QString );
            if (_t _q_method = &client_manager::client_name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (client_manager::*)(QString );
            if (_t _q_method = &client_manager::client_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (client_manager::*)();
            if (_t _q_method = &client_manager::socket_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject *client_manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client_manager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSclient_managerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int client_manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void client_manager::text_message_received(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void client_manager::is_typing_received(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client_manager::init_receiving_file(QString _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void client_manager::reject_receiving_file()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void client_manager::init_receiving_file_client(QString _t1, QString _t2, qint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void client_manager::reject_receiving_file_client(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void client_manager::file_saved(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void client_manager::client_connected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void client_manager::clients_list(QString _t1, QMap<QString,QString> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void client_manager::client_name_changed(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void client_manager::client_disconnected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void client_manager::socket_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
