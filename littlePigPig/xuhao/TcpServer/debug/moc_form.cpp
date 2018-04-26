/****************************************************************************
** Meta object code from reading C++ file 'form.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../form.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Form[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,   28,   32,   32, 0x05,
      33,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   32,   32,   32, 0x08,
      75,   32,   32,   32, 0x08,
      98,   32,   32,   32, 0x08,
     121,   32,   32,   32, 0x08,
     142,   32,   32,   32, 0x08,
     167,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Form[] = {
    "Form\0ensureOperate(QString)\0opt\0\0"
    "exitFromEnsureForm()\0on_btnShow_clicked()\0"
    "on_btnUnlcok_clicked()\0on_btnChange_clicked()\0"
    "on_addUser_clicked()\0on_btnAddGuest_clicked()\0"
    "on_btnExit_clicked()\0"
};

void Form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Form *_t = static_cast<Form *>(_o);
        switch (_id) {
        case 0: _t->ensureOperate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->exitFromEnsureForm(); break;
        case 2: _t->on_btnShow_clicked(); break;
        case 3: _t->on_btnUnlcok_clicked(); break;
        case 4: _t->on_btnChange_clicked(); break;
        case 5: _t->on_addUser_clicked(); break;
        case 6: _t->on_btnAddGuest_clicked(); break;
        case 7: _t->on_btnExit_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Form::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Form::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Form,
      qt_meta_data_Form, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Form::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Form::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Form))
        return static_cast<void*>(const_cast< Form*>(this));
    return QWidget::qt_metacast(_clname);
}

int Form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Form::ensureOperate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Form::exitFromEnsureForm()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
