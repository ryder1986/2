/****************************************************************************
** Meta object code from reading C++ file 'playerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/playerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerWidgetMenu_t {
    QByteArrayData data[11];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerWidgetMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerWidgetMenu_t qt_meta_stringdata_PlayerWidgetMenu = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PlayerWidgetMenu"
QT_MOC_LITERAL(1, 17, 11), // "action_done"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "level1"
QT_MOC_LITERAL(4, 37, 6), // "level2"
QT_MOC_LITERAL(5, 44, 9), // "hide_menu"
QT_MOC_LITERAL(6, 54, 20), // "camera_op_add_region"
QT_MOC_LITERAL(7, 75, 20), // "camera_op_del_region"
QT_MOC_LITERAL(8, 96, 19), // "camera_op_reset_url"
QT_MOC_LITERAL(9, 116, 22), // "processor_op_choose_c4"
QT_MOC_LITERAL(10, 139, 25) // "processor_op_choose_dummy"

    },
    "PlayerWidgetMenu\0action_done\0\0level1\0"
    "level2\0hide_menu\0camera_op_add_region\0"
    "camera_op_del_region\0camera_op_reset_url\0"
    "processor_op_choose_c4\0processor_op_choose_dummy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerWidgetMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   54,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void PlayerWidgetMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerWidgetMenu *_t = static_cast<PlayerWidgetMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->action_done((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->hide_menu(); break;
        case 2: _t->camera_op_add_region((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->camera_op_del_region((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->camera_op_reset_url((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->processor_op_choose_c4((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->processor_op_choose_dummy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PlayerWidgetMenu::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidgetMenu::action_done)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PlayerWidgetMenu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlayerWidgetMenu.data,
      qt_meta_data_PlayerWidgetMenu,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayerWidgetMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerWidgetMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerWidgetMenu.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PlayerWidgetMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PlayerWidgetMenu::action_done(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_PlayerWidget_t {
    QByteArrayData data[60];
    char stringdata0[709];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerWidget_t qt_meta_stringdata_PlayerWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PlayerWidget"
QT_MOC_LITERAL(1, 13, 11), // "click_event"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "PlayerWidget*"
QT_MOC_LITERAL(4, 40, 1), // "w"
QT_MOC_LITERAL(5, 42, 15), // "cam_data_change"
QT_MOC_LITERAL(6, 58, 15), // "CameraInputData"
QT_MOC_LITERAL(7, 74, 8), // "QWidget*"
QT_MOC_LITERAL(8, 83, 13), // "signal_camera"
QT_MOC_LITERAL(9, 97, 2), // "op"
QT_MOC_LITERAL(10, 100, 10), // "JsonPacket"
QT_MOC_LITERAL(11, 111, 4), // "data"
QT_MOC_LITERAL(12, 116, 13), // "signal_region"
QT_MOC_LITERAL(13, 130, 12), // "region_index"
QT_MOC_LITERAL(14, 143, 10), // "add_region"
QT_MOC_LITERAL(15, 154, 21), // "DetectRegionInputData"
QT_MOC_LITERAL(16, 176, 3), // "rct"
QT_MOC_LITERAL(17, 180, 10), // "del_region"
QT_MOC_LITERAL(18, 191, 10), // "set_region"
QT_MOC_LITERAL(19, 202, 10), // "mod_region"
QT_MOC_LITERAL(20, 213, 8), // "mod_data"
QT_MOC_LITERAL(21, 222, 8), // "selected"
QT_MOC_LITERAL(22, 231, 12), // "data_changed"
QT_MOC_LITERAL(23, 244, 11), // "alg_changed"
QT_MOC_LITERAL(24, 256, 5), // "index"
QT_MOC_LITERAL(25, 262, 13), // "timeout_check"
QT_MOC_LITERAL(26, 276, 11), // "handle_menu"
QT_MOC_LITERAL(27, 288, 6), // "level1"
QT_MOC_LITERAL(28, 295, 6), // "level2"
QT_MOC_LITERAL(29, 302, 9), // "hide_menu"
QT_MOC_LITERAL(30, 312, 11), // "right_click"
QT_MOC_LITERAL(31, 324, 3), // "pos"
QT_MOC_LITERAL(32, 328, 7), // "set_url"
QT_MOC_LITERAL(33, 336, 20), // "get_region_test_data"
QT_MOC_LITERAL(34, 357, 3), // "pkt"
QT_MOC_LITERAL(35, 361, 6), // "string"
QT_MOC_LITERAL(36, 368, 17), // "SelectedProcessor"
QT_MOC_LITERAL(37, 386, 19), // "get_dummy_test_data"
QT_MOC_LITERAL(38, 406, 23), // "DummyProcessorInputData"
QT_MOC_LITERAL(39, 430, 16), // "get_c4_test_data"
QT_MOC_LITERAL(40, 447, 20), // "C4ProcessorInputData"
QT_MOC_LITERAL(41, 468, 13), // "set_processor"
QT_MOC_LITERAL(42, 482, 15), // "processor_label"
QT_MOC_LITERAL(43, 498, 19), // "set_processor_dummy"
QT_MOC_LITERAL(44, 518, 7), // "checked"
QT_MOC_LITERAL(45, 526, 16), // "set_processor_c4"
QT_MOC_LITERAL(46, 543, 15), // "set_region_data"
QT_MOC_LITERAL(47, 559, 7), // "timeout"
QT_MOC_LITERAL(48, 567, 13), // "get_min_point"
QT_MOC_LITERAL(49, 581, 15), // "vector<VdPoint>"
QT_MOC_LITERAL(50, 597, 16), // "ExpectedAreaVers"
QT_MOC_LITERAL(51, 614, 4), // "int&"
QT_MOC_LITERAL(52, 619, 1), // "x"
QT_MOC_LITERAL(53, 621, 1), // "y"
QT_MOC_LITERAL(54, 623, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(55, 638, 12), // "QMouseEvent*"
QT_MOC_LITERAL(56, 651, 1), // "e"
QT_MOC_LITERAL(57, 653, 15), // "mousePressEvent"
QT_MOC_LITERAL(58, 669, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(59, 687, 21) // "mouseDoubleClickEvent"

    },
    "PlayerWidget\0click_event\0\0PlayerWidget*\0"
    "w\0cam_data_change\0CameraInputData\0"
    "QWidget*\0signal_camera\0op\0JsonPacket\0"
    "data\0signal_region\0region_index\0"
    "add_region\0DetectRegionInputData\0rct\0"
    "del_region\0set_region\0mod_region\0"
    "mod_data\0selected\0data_changed\0"
    "alg_changed\0index\0timeout_check\0"
    "handle_menu\0level1\0level2\0hide_menu\0"
    "right_click\0pos\0set_url\0get_region_test_data\0"
    "pkt\0string\0SelectedProcessor\0"
    "get_dummy_test_data\0DummyProcessorInputData\0"
    "get_c4_test_data\0C4ProcessorInputData\0"
    "set_processor\0processor_label\0"
    "set_processor_dummy\0checked\0"
    "set_processor_c4\0set_region_data\0"
    "timeout\0get_min_point\0vector<VdPoint>\0"
    "ExpectedAreaVers\0int&\0x\0y\0mouseMoveEvent\0"
    "QMouseEvent*\0e\0mousePressEvent\0"
    "mouseReleaseEvent\0mouseDoubleClickEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  174,    2, 0x06 /* Public */,
       5,    2,  179,    2, 0x06 /* Public */,
       8,    3,  184,    2, 0x06 /* Public */,
      12,    4,  191,    2, 0x06 /* Public */,
      14,    3,  200,    2, 0x06 /* Public */,
      17,    2,  207,    2, 0x06 /* Public */,
      18,    2,  212,    2, 0x06 /* Public */,
      19,    3,  217,    2, 0x06 /* Public */,
      21,    1,  224,    2, 0x06 /* Public */,
      22,    0,  227,    2, 0x06 /* Public */,
      23,    1,  228,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    0,  231,    2, 0x0a /* Public */,
      26,    2,  232,    2, 0x0a /* Public */,
      29,    0,  237,    2, 0x0a /* Public */,
      30,    1,  238,    2, 0x0a /* Public */,
      14,    1,  241,    2, 0x0a /* Public */,
      17,    1,  244,    2, 0x0a /* Public */,
      32,    1,  247,    2, 0x0a /* Public */,
      33,    2,  250,    2, 0x0a /* Public */,
      37,    0,  255,    2, 0x0a /* Public */,
      39,    0,  256,    2, 0x0a /* Public */,
      41,    1,  257,    2, 0x0a /* Public */,
      43,    1,  260,    2, 0x0a /* Public */,
      45,    1,  263,    2, 0x0a /* Public */,
      18,    1,  266,    2, 0x0a /* Public */,
      46,    1,  269,    2, 0x0a /* Public */,
      47,    0,  272,    2, 0x0a /* Public */,
      48,    3,  273,    2, 0x0a /* Public */,
      54,    1,  280,    2, 0x0a /* Public */,
      57,    1,  283,    2, 0x0a /* Public */,
      58,    1,  286,    2, 0x0a /* Public */,
      59,    1,  289,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    2,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 7,    2,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 10,    4,    9,   11,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, 0x80000000 | 10,    4,   13,    9,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15, 0x80000000 | 7,   13,   16,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   13,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   13,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 7,   13,   20,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   27,   28,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   31,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    0x80000000 | 15, 0x80000000 | 10, 0x80000000 | 35,   34,   36,
    0x80000000 | 38,
    0x80000000 | 40,
    QMetaType::Void, 0x80000000 | 35,   42,
    QMetaType::Void, QMetaType::Bool,   44,
    QMetaType::Void, QMetaType::Bool,   44,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 49, 0x80000000 | 51, 0x80000000 | 51,   50,   52,   53,
    QMetaType::Void, 0x80000000 | 55,   56,
    QMetaType::Void, 0x80000000 | 55,   56,
    QMetaType::Void, 0x80000000 | 55,   56,
    QMetaType::Void, 0x80000000 | 55,   56,

       0        // eod
};

void PlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerWidget *_t = static_cast<PlayerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->click_event((*reinterpret_cast< PlayerWidget*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->cam_data_change((*reinterpret_cast< CameraInputData(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 2: _t->signal_camera((*reinterpret_cast< PlayerWidget*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< JsonPacket(*)>(_a[3]))); break;
        case 3: _t->signal_region((*reinterpret_cast< PlayerWidget*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< JsonPacket(*)>(_a[4]))); break;
        case 4: _t->add_region((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< DetectRegionInputData(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        case 5: _t->del_region((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 6: _t->set_region((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 7: _t->mod_region((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< JsonPacket(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        case 8: _t->selected((*reinterpret_cast< PlayerWidget*(*)>(_a[1]))); break;
        case 9: _t->data_changed(); break;
        case 10: _t->alg_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->timeout_check(); break;
        case 12: _t->handle_menu((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->hide_menu(); break;
        case 14: _t->right_click((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 15: _t->add_region((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->del_region((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->set_url((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: { DetectRegionInputData _r = _t->get_region_test_data((*reinterpret_cast< JsonPacket(*)>(_a[1])),(*reinterpret_cast< string(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< DetectRegionInputData*>(_a[0]) = std::move(_r); }  break;
        case 19: { DummyProcessorInputData _r = _t->get_dummy_test_data();
            if (_a[0]) *reinterpret_cast< DummyProcessorInputData*>(_a[0]) = std::move(_r); }  break;
        case 20: { C4ProcessorInputData _r = _t->get_c4_test_data();
            if (_a[0]) *reinterpret_cast< C4ProcessorInputData*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->set_processor((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 22: _t->set_processor_dummy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->set_processor_c4((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->set_region((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->set_region_data((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->timeout(); break;
        case 27: _t->get_min_point((*reinterpret_cast< vector<VdPoint>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 29: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 30: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 31: _t->mouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
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
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerWidget* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PlayerWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PlayerWidget::*_t)(PlayerWidget * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::click_event)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(CameraInputData , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::cam_data_change)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(PlayerWidget * , int , JsonPacket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::signal_camera)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(PlayerWidget * , int , int , JsonPacket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::signal_region)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(int , DetectRegionInputData , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::add_region)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(int , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::del_region)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(int , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::set_region)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(int , JsonPacket , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::mod_region)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(PlayerWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::selected)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::data_changed)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (PlayerWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::alg_changed)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject PlayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayerWidget.data,
      qt_meta_data_PlayerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void PlayerWidget::click_event(PlayerWidget * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerWidget::cam_data_change(CameraInputData _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayerWidget::signal_camera(PlayerWidget * _t1, int _t2, JsonPacket _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayerWidget::signal_region(PlayerWidget * _t1, int _t2, int _t3, JsonPacket _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayerWidget::add_region(int _t1, DetectRegionInputData _t2, QWidget * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlayerWidget::del_region(int _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PlayerWidget::set_region(int _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PlayerWidget::mod_region(int _t1, JsonPacket _t2, QWidget * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PlayerWidget::selected(PlayerWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PlayerWidget::data_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void PlayerWidget::alg_changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
