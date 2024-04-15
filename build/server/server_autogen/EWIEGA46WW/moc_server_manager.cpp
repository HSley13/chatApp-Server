/****************************************************************************
** Meta object code from reading C++ file 'server_manager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/server/server_manager.h"
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
#error "The header file 'server_manager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSserver_managerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSserver_managerENDCLASS = QtMocHelpers::stringData(
    "server_manager",
    "new_client_connected",
    "",
    "QTcpSocket*",
    "client",
    "new_client_disconnected",
    "text_message_received",
    "sender",
    "receiver",
    "message",
    "client_name_changed",
    "original_name",
    "old_name",
    "name",
    "is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "init_receiving_file_client",
    "file_saved",
    "path",
    "reject_receiving_file",
    "on_new_connection",
    "on_client_disconnected",
    "on_ready_read",
    "on_text_for_other_clients"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSserver_managerENDCLASS_t {
    uint offsetsAndSizes[52];
    char stringdata0[15];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[24];
    char stringdata6[22];
    char stringdata7[7];
    char stringdata8[9];
    char stringdata9[8];
    char stringdata10[20];
    char stringdata11[14];
    char stringdata12[9];
    char stringdata13[5];
    char stringdata14[19];
    char stringdata15[20];
    char stringdata16[10];
    char stringdata17[10];
    char stringdata18[27];
    char stringdata19[11];
    char stringdata20[5];
    char stringdata21[22];
    char stringdata22[18];
    char stringdata23[23];
    char stringdata24[14];
    char stringdata25[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSserver_managerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSserver_managerENDCLASS_t qt_meta_stringdata_CLASSserver_managerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "server_manager"
        QT_MOC_LITERAL(15, 20),  // "new_client_connected"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(49, 6),  // "client"
        QT_MOC_LITERAL(56, 23),  // "new_client_disconnected"
        QT_MOC_LITERAL(80, 21),  // "text_message_received"
        QT_MOC_LITERAL(102, 6),  // "sender"
        QT_MOC_LITERAL(109, 8),  // "receiver"
        QT_MOC_LITERAL(118, 7),  // "message"
        QT_MOC_LITERAL(126, 19),  // "client_name_changed"
        QT_MOC_LITERAL(146, 13),  // "original_name"
        QT_MOC_LITERAL(160, 8),  // "old_name"
        QT_MOC_LITERAL(169, 4),  // "name"
        QT_MOC_LITERAL(174, 18),  // "is_typing_received"
        QT_MOC_LITERAL(193, 19),  // "init_receiving_file"
        QT_MOC_LITERAL(213, 9),  // "file_name"
        QT_MOC_LITERAL(223, 9),  // "file_size"
        QT_MOC_LITERAL(233, 26),  // "init_receiving_file_client"
        QT_MOC_LITERAL(260, 10),  // "file_saved"
        QT_MOC_LITERAL(271, 4),  // "path"
        QT_MOC_LITERAL(276, 21),  // "reject_receiving_file"
        QT_MOC_LITERAL(298, 17),  // "on_new_connection"
        QT_MOC_LITERAL(316, 22),  // "on_client_disconnected"
        QT_MOC_LITERAL(339, 13),  // "on_ready_read"
        QT_MOC_LITERAL(353, 25)   // "on_text_for_other_clients"
    },
    "server_manager",
    "new_client_connected",
    "",
    "QTcpSocket*",
    "client",
    "new_client_disconnected",
    "text_message_received",
    "sender",
    "receiver",
    "message",
    "client_name_changed",
    "original_name",
    "old_name",
    "name",
    "is_typing_received",
    "init_receiving_file",
    "file_name",
    "file_size",
    "init_receiving_file_client",
    "file_saved",
    "path",
    "reject_receiving_file",
    "on_new_connection",
    "on_client_disconnected",
    "on_ready_read",
    "on_text_for_other_clients"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSserver_managerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    1 /* Public */,
       5,    1,   95,    2, 0x06,    3 /* Public */,
       6,    3,   98,    2, 0x06,    5 /* Public */,
      10,    3,  105,    2, 0x06,    9 /* Public */,
      14,    2,  112,    2, 0x06,   13 /* Public */,
      15,    3,  117,    2, 0x06,   16 /* Public */,
      18,    3,  124,    2, 0x06,   20 /* Public */,
      19,    1,  131,    2, 0x06,   24 /* Public */,
      21,    1,  134,    2, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      22,    0,  137,    2, 0x08,   28 /* Private */,
      23,    0,  138,    2, 0x08,   29 /* Private */,
      24,    0,  139,    2, 0x08,   30 /* Private */,
      25,    3,  140,    2, 0x0a,   31 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    7,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,   16,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject server_manager::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSserver_managerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSserver_managerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSserver_managerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<server_manager, std::true_type>,
        // method 'new_client_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        // method 'new_client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'init_receiving_file_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'reject_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_new_connection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ready_read'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_text_for_other_clients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void server_manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<server_manager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->new_client_connected((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1]))); break;
        case 1: _t->new_client_disconnected((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1]))); break;
        case 2: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 4: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 6: _t->init_receiving_file_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 7: _t->file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->reject_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->on_new_connection(); break;
        case 10: _t->on_client_disconnected(); break;
        case 11: _t->on_ready_read(); break;
        case 12: _t->on_text_for_other_clients((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (server_manager::*)(QTcpSocket * );
            if (_t _q_method = &server_manager::new_client_connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QTcpSocket * );
            if (_t _q_method = &server_manager::new_client_disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString , QString , QString );
            if (_t _q_method = &server_manager::text_message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString , QString , QString );
            if (_t _q_method = &server_manager::client_name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString , QString );
            if (_t _q_method = &server_manager::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString , QString , qint64 );
            if (_t _q_method = &server_manager::init_receiving_file; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString , QString , QString );
            if (_t _q_method = &server_manager::init_receiving_file_client; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString );
            if (_t _q_method = &server_manager::file_saved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString );
            if (_t _q_method = &server_manager::reject_receiving_file; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject *server_manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server_manager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSserver_managerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int server_manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void server_manager::new_client_connected(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void server_manager::new_client_disconnected(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void server_manager::text_message_received(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void server_manager::client_name_changed(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void server_manager::is_typing_received(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void server_manager::init_receiving_file(QString _t1, QString _t2, qint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void server_manager::init_receiving_file_client(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void server_manager::file_saved(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void server_manager::reject_receiving_file(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
