/****************************************************************************
** Meta object code from reading C++ file 'tcpmgr.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../tcpmgr.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN6TcpMgrE_t {};
} // unnamed namespace

template <> constexpr inline auto TcpMgr::qt_create_metaobjectdata<qt_meta_tag_ZN6TcpMgrE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TcpMgr",
        "sig_conn_success",
        "",
        "bsueccess",
        "sig_send_data",
        "ReqType",
        "reqid",
        "data",
        "sig_login_failed",
        "err",
        "sig_swich_chatdlg",
        "slot_tcp_connect",
        "ServerInfo",
        "si",
        "slot_send_data"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_conn_success'
        QtMocHelpers::SignalData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'sig_send_data'
        QtMocHelpers::SignalData<void(ReqType, QString)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { QMetaType::QString, 7 },
        }}),
        // Signal 'sig_login_failed'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Signal 'sig_swich_chatdlg'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_tcp_connect'
        QtMocHelpers::SlotData<void(ServerInfo)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'slot_send_data'
        QtMocHelpers::SlotData<void(ReqType, QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { QMetaType::QString, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TcpMgr, qt_meta_tag_ZN6TcpMgrE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TcpMgr::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6TcpMgrE_t>.metaTypes,
    nullptr
} };

void TcpMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TcpMgr *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_conn_success((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sig_send_data((*reinterpret_cast< std::add_pointer_t<ReqType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->sig_login_failed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->sig_swich_chatdlg(); break;
        case 4: _t->slot_tcp_connect((*reinterpret_cast< std::add_pointer_t<ServerInfo>>(_a[1]))); break;
        case 5: _t->slot_send_data((*reinterpret_cast< std::add_pointer_t<ReqType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(bool )>(_a, &TcpMgr::sig_conn_success, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(ReqType , QString )>(_a, &TcpMgr::sig_send_data, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(int )>(_a, &TcpMgr::sig_login_failed, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)()>(_a, &TcpMgr::sig_swich_chatdlg, 3))
            return;
    }
}

const QMetaObject *TcpMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "::SingteTon<TcpMgr>"))
        return static_cast< ::SingteTon<TcpMgr>*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<TcpMgr>"))
        return static_cast< std::enable_shared_from_this<TcpMgr>*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TcpMgr::sig_conn_success(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TcpMgr::sig_send_data(ReqType _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void TcpMgr::sig_login_failed(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void TcpMgr::sig_swich_chatdlg()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
