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
    "old_name",
    "name",
    "is_typing_received",
    "sender",
    "receiver",
    "text_for_other_client",
    "message",
    "file_for_other_client",
    "file_name",
    "reject_receiving_file_for_other_clients",
    "send_message",
    "folder",
    "send_file",
    "on_text_message_received",
    "on_is_typing_received",
    "on_init_receiving_file",
    "file_size",
    "on_file_saved",
    "path",
    "on_client_name_changed",
    "client_name",
    "on_reject_receiving_file"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[19];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[5];
    char stringdata5[19];
    char stringdata6[7];
    char stringdata7[9];
    char stringdata8[22];
    char stringdata9[8];
    char stringdata10[22];
    char stringdata11[10];
    char stringdata12[40];
    char stringdata13[13];
    char stringdata14[7];
    char stringdata15[10];
    char stringdata16[25];
    char stringdata17[22];
    char stringdata18[23];
    char stringdata19[10];
    char stringdata20[14];
    char stringdata21[5];
    char stringdata22[23];
    char stringdata23[12];
    char stringdata24[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSserver_chat_windowENDCLASS_t qt_meta_stringdata_CLASSserver_chat_windowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "server_chat_window"
        QT_MOC_LITERAL(19, 19),  // "client_name_changed"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 8),  // "old_name"
        QT_MOC_LITERAL(49, 4),  // "name"
        QT_MOC_LITERAL(54, 18),  // "is_typing_received"
        QT_MOC_LITERAL(73, 6),  // "sender"
        QT_MOC_LITERAL(80, 8),  // "receiver"
        QT_MOC_LITERAL(89, 21),  // "text_for_other_client"
        QT_MOC_LITERAL(111, 7),  // "message"
        QT_MOC_LITERAL(119, 21),  // "file_for_other_client"
        QT_MOC_LITERAL(141, 9),  // "file_name"
        QT_MOC_LITERAL(151, 39),  // "reject_receiving_file_for_oth..."
        QT_MOC_LITERAL(191, 12),  // "send_message"
        QT_MOC_LITERAL(204, 6),  // "folder"
        QT_MOC_LITERAL(211, 9),  // "send_file"
        QT_MOC_LITERAL(221, 24),  // "on_text_message_received"
        QT_MOC_LITERAL(246, 21),  // "on_is_typing_received"
        QT_MOC_LITERAL(268, 22),  // "on_init_receiving_file"
        QT_MOC_LITERAL(291, 9),  // "file_size"
        QT_MOC_LITERAL(301, 13),  // "on_file_saved"
        QT_MOC_LITERAL(315, 4),  // "path"
        QT_MOC_LITERAL(320, 22),  // "on_client_name_changed"
        QT_MOC_LITERAL(343, 11),  // "client_name"
        QT_MOC_LITERAL(355, 24)   // "on_reject_receiving_file"
    },
    "server_chat_window",
    "client_name_changed",
    "",
    "old_name",
    "name",
    "is_typing_received",
    "sender",
    "receiver",
    "text_for_other_client",
    "message",
    "file_for_other_client",
    "file_name",
    "reject_receiving_file_for_other_clients",
    "send_message",
    "folder",
    "send_file",
    "on_text_message_received",
    "on_is_typing_received",
    "on_init_receiving_file",
    "file_size",
    "on_file_saved",
    "path",
    "on_client_name_changed",
    "client_name",
    "on_reject_receiving_file"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSserver_chat_windowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   98,    2, 0x06,    1 /* Public */,
       5,    2,  103,    2, 0x06,    4 /* Public */,
       8,    3,  108,    2, 0x06,    7 /* Public */,
      10,    3,  115,    2, 0x06,   11 /* Public */,
      12,    2,  122,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,  127,    2, 0x08,   18 /* Private */,
      14,    0,  128,    2, 0x08,   19 /* Private */,
      15,    0,  129,    2, 0x08,   20 /* Private */,
      16,    3,  130,    2, 0x08,   21 /* Private */,
      17,    2,  137,    2, 0x08,   25 /* Private */,
      18,    3,  142,    2, 0x08,   28 /* Private */,
      20,    1,  149,    2, 0x08,   32 /* Private */,
      22,    2,  152,    2, 0x08,   34 /* Private */,
      24,    1,  157,    2, 0x08,   37 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::LongLong,    6,   11,   19,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   23,
    QMetaType::Void, QMetaType::QString,    6,

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
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'text_for_other_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'file_for_other_client'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'reject_receiving_file_for_other_clients'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'send_message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'folder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'send_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_text_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_is_typing_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_init_receiving_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'on_file_saved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_client_name_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'on_reject_receiving_file'
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
        case 0: _t->client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->text_for_other_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->file_for_other_client((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 4: _t->reject_receiving_file_for_other_clients((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->send_message(); break;
        case 6: _t->folder(); break;
        case 7: _t->send_file(); break;
        case 8: _t->on_text_message_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 9: _t->on_is_typing_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->on_init_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[3]))); break;
        case 11: _t->on_file_saved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->on_client_name_changed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->on_reject_receiving_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (server_chat_window::*)(QString , QString );
            if (_t _q_method = &server_chat_window::client_name_changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (server_chat_window::*)(QString , QString );
            if (_t _q_method = &server_chat_window::is_typing_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (server_chat_window::*)(QString , QString , QString );
            if (_t _q_method = &server_chat_window::text_for_other_client; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (server_chat_window::*)(QString , QString , QString );
            if (_t _q_method = &server_chat_window::file_for_other_client; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (server_chat_window::*)(QString , QString );
            if (_t _q_method = &server_chat_window::reject_receiving_file_for_other_clients; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void server_chat_window::client_name_changed(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void server_chat_window::is_typing_received(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void server_chat_window::text_for_other_client(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void server_chat_window::file_for_other_client(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void server_chat_window::reject_receiving_file_for_other_clients(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
