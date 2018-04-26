/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *btnUnlcok;
    QPushButton *btnChange;
    QPushButton *btnShow;
    QPushButton *addUser;
    QPushButton *btnAddGuest;
    QPushButton *btnExit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(800, 480);
        Form->setStyleSheet(QString::fromUtf8("QWidget#Form{\n"
"background-image: url(:/image/baoan.jpg);}"));
        btnUnlcok = new QPushButton(Form);
        btnUnlcok->setObjectName(QString::fromUtf8("btnUnlcok"));
        btnUnlcok->setGeometry(QRect(149, 340, 71, 41));
        btnUnlcok->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));
        btnChange = new QPushButton(Form);
        btnChange->setObjectName(QString::fromUtf8("btnChange"));
        btnChange->setGeometry(QRect(239, 280, 71, 41));
        btnChange->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));
        btnShow = new QPushButton(Form);
        btnShow->setObjectName(QString::fromUtf8("btnShow"));
        btnShow->setGeometry(QRect(149, 280, 71, 41));
        btnShow->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));
        addUser = new QPushButton(Form);
        addUser->setObjectName(QString::fromUtf8("addUser"));
        addUser->setGeometry(QRect(240, 340, 71, 41));
        addUser->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));
        btnAddGuest = new QPushButton(Form);
        btnAddGuest->setObjectName(QString::fromUtf8("btnAddGuest"));
        btnAddGuest->setGeometry(QRect(240, 400, 71, 41));
        btnAddGuest->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));
        btnExit = new QPushButton(Form);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(150, 400, 71, 41));
        btnExit->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"color: rgb(0,0,0);\n"
"background\357\274\232transparent;\n"
"border:3px groove;\n"
"border-radius:7px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"pading-left:6px;\n"
"padding-top:6px;\n"
"}"));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        btnUnlcok->setText(QApplication::translate("Form", "\350\247\243\351\224\201", 0, QApplication::UnicodeUTF8));
        btnChange->setText(QApplication::translate("Form", " \346\233\264\346\224\271\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        btnShow->setText(QApplication::translate("Form", "\346\237\245\347\234\213\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        addUser->setText(QApplication::translate("Form", "\346\267\273\345\212\240\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        btnAddGuest->setText(QApplication::translate("Form", "\346\267\273\345\212\240\346\235\245\345\256\276", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("Form", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
