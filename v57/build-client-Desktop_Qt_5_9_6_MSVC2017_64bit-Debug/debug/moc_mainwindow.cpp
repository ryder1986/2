/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[17];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 22), // "signal_get_config_done"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "string"
QT_MOC_LITERAL(4, 38, 18), // "need_update_config"
QT_MOC_LITERAL(5, 57, 12), // "connect_done"
QT_MOC_LITERAL(6, 70, 7), // "get_ret"
QT_MOC_LITERAL(7, 78, 9), // "send_done"
QT_MOC_LITERAL(8, 88, 10), // "server_msg"
QT_MOC_LITERAL(9, 99, 16), // "handle_connected"
QT_MOC_LITERAL(10, 116, 18), // "handle_server_msg1"
QT_MOC_LITERAL(11, 135, 17), // "handle_server_msg"
QT_MOC_LITERAL(12, 153, 17), // "connect_to_server"
QT_MOC_LITERAL(13, 171, 2), // "ip"
QT_MOC_LITERAL(14, 174, 12), // "displayError"
QT_MOC_LITERAL(15, 187, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(16, 216, 11) // "socketError"

    },
    "Client\0signal_get_config_done\0\0string\0"
    "need_update_config\0connect_done\0get_ret\0"
    "send_done\0server_msg\0handle_connected\0"
    "handle_server_msg1\0handle_server_msg\0"
    "connect_to_server\0ip\0displayError\0"
    "QAbstractSocket::SocketError\0socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       4,    0,   74,    2, 0x06 /* Public */,
       5,    0,   75,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,
       7,    1,   79,    2, 0x06 /* Public */,
       8,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   85,    2, 0x0a /* Public */,
      10,    0,   86,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      14,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_get_config_done((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2]))); break;
        case 1: _t->need_update_config(); break;
        case 2: _t->connect_done(); break;
        case 3: _t->get_ret((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->send_done((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->server_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->handle_connected(); break;
        case 7: _t->handle_server_msg1(); break;
        case 8: _t->handle_server_msg(); break;
        case 9: _t->connect_to_server((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Client::*_t)(bool , string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::signal_get_config_done)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::need_update_config)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::connect_done)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::get_ret)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::send_done)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::server_msg)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Client::signal_get_config_done(bool _t1, string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Client::need_update_config()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Client::connect_done()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Client::get_ret(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::send_done(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::server_msg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_ServerReplyCheckRouting_t {
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerReplyCheckRouting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerReplyCheckRouting_t qt_meta_stringdata_ServerReplyCheckRouting = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ServerReplyCheckRouting"
QT_MOC_LITERAL(1, 24, 11), // "resultReady"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "result"
QT_MOC_LITERAL(4, 44, 11), // "check_reply"
QT_MOC_LITERAL(5, 56, 11), // "QUdpSocket*"
QT_MOC_LITERAL(6, 68, 19) // "udp_skt_find_server"

    },
    "ServerReplyCheckRouting\0resultReady\0"
    "\0result\0check_reply\0QUdpSocket*\0"
    "udp_skt_find_server"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerReplyCheckRouting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void ServerReplyCheckRouting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerReplyCheckRouting *_t = static_cast<ServerReplyCheckRouting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->check_reply((*reinterpret_cast< QUdpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QUdpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ServerReplyCheckRouting::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerReplyCheckRouting::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ServerReplyCheckRouting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerReplyCheckRouting.data,
      qt_meta_data_ServerReplyCheckRouting,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ServerReplyCheckRouting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerReplyCheckRouting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerReplyCheckRouting.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerReplyCheckRouting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ServerReplyCheckRouting::resultReady(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ServerInfoSearcher_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerInfoSearcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerInfoSearcher_t qt_meta_stringdata_ServerInfoSearcher = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ServerInfoSearcher"
QT_MOC_LITERAL(1, 19, 12), // "begin_search"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "QUdpSocket*"
QT_MOC_LITERAL(4, 45, 19), // "udp_skt_find_server"
QT_MOC_LITERAL(5, 65, 7), // "find_ip"
QT_MOC_LITERAL(6, 73, 2), // "ip"
QT_MOC_LITERAL(7, 76, 8) // "ip_found"

    },
    "ServerInfoSearcher\0begin_search\0\0"
    "QUdpSocket*\0udp_skt_find_server\0find_ip\0"
    "ip\0ip_found"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerInfoSearcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void ServerInfoSearcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerInfoSearcher *_t = static_cast<ServerInfoSearcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->begin_search((*reinterpret_cast< QUdpSocket*(*)>(_a[1]))); break;
        case 1: _t->find_ip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ip_found((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QUdpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ServerInfoSearcher::*_t)(QUdpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerInfoSearcher::begin_search)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ServerInfoSearcher::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerInfoSearcher::find_ip)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ServerInfoSearcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerInfoSearcher.data,
      qt_meta_data_ServerInfoSearcher,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ServerInfoSearcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerInfoSearcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerInfoSearcher.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerInfoSearcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ServerInfoSearcher::begin_search(QUdpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerInfoSearcher::find_ip(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[31];
    char stringdata0[491];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "dataReceived"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "player_event"
QT_MOC_LITERAL(4, 38, 13), // "PlayerWidget*"
QT_MOC_LITERAL(5, 52, 1), // "w"
QT_MOC_LITERAL(6, 54, 1), // "t"
QT_MOC_LITERAL(7, 56, 11), // "slot_camera"
QT_MOC_LITERAL(8, 68, 2), // "op"
QT_MOC_LITERAL(9, 71, 10), // "JsonPacket"
QT_MOC_LITERAL(10, 82, 4), // "data"
QT_MOC_LITERAL(11, 87, 23), // "generate_current_config"
QT_MOC_LITERAL(12, 111, 15), // "CameraInputData"
QT_MOC_LITERAL(13, 127, 1), // "d"
QT_MOC_LITERAL(14, 129, 8), // "QWidget*"
QT_MOC_LITERAL(15, 138, 8), // "ip_found"
QT_MOC_LITERAL(16, 147, 2), // "ip"
QT_MOC_LITERAL(17, 150, 10), // "server_msg"
QT_MOC_LITERAL(18, 161, 3), // "msg"
QT_MOC_LITERAL(19, 165, 28), // "on_pushButton_search_clicked"
QT_MOC_LITERAL(20, 194, 28), // "on_comboBox_search_activated"
QT_MOC_LITERAL(21, 223, 4), // "arg1"
QT_MOC_LITERAL(22, 228, 26), // "on_pushButton_send_clicked"
QT_MOC_LITERAL(23, 255, 28), // "on_pushButton_recive_clicked"
QT_MOC_LITERAL(24, 284, 31), // "on_pushButton_getconfig_clicked"
QT_MOC_LITERAL(25, 316, 27), // "on_pushButton_start_clicked"
QT_MOC_LITERAL(26, 344, 26), // "on_pushButton_stop_clicked"
QT_MOC_LITERAL(27, 371, 31), // "on_pushButton_setconfig_clicked"
QT_MOC_LITERAL(28, 403, 28), // "on_pushButton_addcam_clicked"
QT_MOC_LITERAL(29, 432, 28), // "on_pushButton_delcam_clicked"
QT_MOC_LITERAL(30, 461, 29) // "on_pushButton_connect_clicked"

    },
    "MainWindow\0dataReceived\0\0player_event\0"
    "PlayerWidget*\0w\0t\0slot_camera\0op\0"
    "JsonPacket\0data\0generate_current_config\0"
    "CameraInputData\0d\0QWidget*\0ip_found\0"
    "ip\0server_msg\0msg\0on_pushButton_search_clicked\0"
    "on_comboBox_search_activated\0arg1\0"
    "on_pushButton_send_clicked\0"
    "on_pushButton_recive_clicked\0"
    "on_pushButton_getconfig_clicked\0"
    "on_pushButton_start_clicked\0"
    "on_pushButton_stop_clicked\0"
    "on_pushButton_setconfig_clicked\0"
    "on_pushButton_addcam_clicked\0"
    "on_pushButton_delcam_clicked\0"
    "on_pushButton_connect_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    2,  100,    2, 0x08 /* Private */,
       7,    3,  105,    2, 0x08 /* Private */,
      11,    2,  112,    2, 0x08 /* Private */,
      15,    1,  117,    2, 0x08 /* Private */,
      17,    1,  120,    2, 0x08 /* Private */,
      19,    0,  123,    2, 0x08 /* Private */,
      20,    1,  124,    2, 0x08 /* Private */,
      22,    0,  127,    2, 0x08 /* Private */,
      23,    0,  128,    2, 0x08 /* Private */,
      24,    0,  129,    2, 0x08 /* Private */,
      25,    0,  130,    2, 0x08 /* Private */,
      26,    0,  131,    2, 0x08 /* Private */,
      27,    0,  132,    2, 0x08 /* Private */,
      28,    0,  133,    2, 0x08 /* Private */,
      29,    0,  134,    2, 0x08 /* Private */,
      30,    0,  135,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, 0x80000000 | 9,    5,    8,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,    5,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived(); break;
        case 1: _t->player_event((*reinterpret_cast< PlayerWidget*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_camera((*reinterpret_cast< PlayerWidget*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< JsonPacket(*)>(_a[3]))); break;
        case 3: _t->generate_current_config((*reinterpret_cast< CameraInputData(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 4: _t->ip_found((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->server_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_pushButton_search_clicked(); break;
        case 7: _t->on_comboBox_search_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_send_clicked(); break;
        case 9: _t->on_pushButton_recive_clicked(); break;
        case 10: _t->on_pushButton_getconfig_clicked(); break;
        case 11: _t->on_pushButton_start_clicked(); break;
        case 12: _t->on_pushButton_stop_clicked(); break;
        case 13: _t->on_pushButton_setconfig_clicked(); break;
        case 14: _t->on_pushButton_addcam_clicked(); break;
        case 15: _t->on_pushButton_delcam_clicked(); break;
        case 16: _t->on_pushButton_connect_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
