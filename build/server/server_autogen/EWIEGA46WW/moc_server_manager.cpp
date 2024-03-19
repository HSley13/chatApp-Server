/****************************************************************************
** Meta object code from reading C++ file 'server_manager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chat/server/server_manager.h"
#include <QtGui/qtextcursor.h>
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
    "connected",
    "disconnected",
    "text_message_received",
    "message",
    "name_changed",
    "name",
    "is_typing_received",
    "new_connection",
    "client_disconnected",
    "ready_read"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSserver_managerENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[15];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[24];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[22];
    char stringdata9[8];
    char stringdata10[13];
    char stringdata11[5];
    char stringdata12[19];
    char stringdata13[15];
    char stringdata14[20];
    char stringdata15[11];
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
        QT_MOC_LITERAL(80, 9),  // "connected"
        QT_MOC_LITERAL(90, 12),  // "disconnected"
        QT_MOC_LITERAL(103, 21),  // "text_message_received"
        QT_MOC_LITERAL(125, 7),  // "message"
        QT_MOC_LITERAL(133, 12),  // "name_changed"
        QT_MOC_LITERAL(146, 4),  // "name"
        QT_MOC_LITERAL(151, 18),  // "is_typing_received"
        QT_MOC_LITERAL(170, 14),  // "new_connection"
        QT_MOC_LITERAL(185, 19),  // "client_disconnected"
        QT_MOC_LITERAL(205, 10)   // "ready_read"
    },
    "server_manager",
    "new_client_connected",
    "",
    "QTcpSocket*",
    "client",
    "new_client_disconnected",
    "connected",
    "disconnected",
    "text_message_received",
    "message",
    "name_changed",
    "name",
    "is_typing_received",
    "new_connection",
    "client_disconnected",
    "ready_read"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSserver_managerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    1,   77,    2, 0x06,    3 /* Public */,
       6,    0,   80,    2, 0x06,    5 /* Public */,
       7,    0,   81,    2, 0x06,    6 /* Public */,
       8,    1,   82,    2, 0x06,    7 /* Public */,
      10,    1,   85,    2, 0x06,    9 /* Public */,
      12,    0,   88,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,   89,    2, 0x08,   12 /* Private */,
      14,    0,   90,    2, 0x08,   13 /* Private */,
      15,    0,   91,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'new_connection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'client_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ready_read'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
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
        case 2: _t->connected(); break;
        case 3: _t->disconnected(); break;
        case 4: _t->text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->is_typing_received(); break;
        case 7: _t->new_connection(); break;
        case 8: _t->client_disconnected(); break;
        case 9: _t->ready_read(); break;
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
            using _t = void (server_manager::*)();
            if (_t _q_method = &server_manager::connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (server_manager::*)();
            if (_t _q_method = &server_manager::disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString );
            if (_t _q_method = &server_manager::text_message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (server_manager::*)(QString );
            if (_t _q_method = &server_manager::name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (server_manager::*)();
            if (_t _q_method = &server_manager::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
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
void server_manager::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void server_manager::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void server_manager::text_message_received(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void server_manager::name_changed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void server_manager::is_typing_received()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
