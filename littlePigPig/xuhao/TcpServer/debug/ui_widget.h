/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QPushButton *btnUser;
    QPushButton *btnGuest;
    QPushButton *btnEnsure;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 480);
        Widget->setStyleSheet(QString::fromUtf8("QWidget#Widget\n"
"{\n"
"image: url(:/image/test.jpg);\n"
"}"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, -10, 581, 161));
        QFont font;
        font.setFamily(QString::fromUtf8("Aharoni"));
        font.setPointSize(48);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        btnUser = new QPushButton(Widget);
        btnUser->setObjectName(QString::fromUtf8("btnUser"));
        btnUser->setGeometry(QRect(10, 310, 200, 150));
        QFont font1;
        font1.setPointSize(50);
        btnUser->setFont(font1);
        btnUser->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        btnGuest = new QPushButton(Widget);
        btnGuest->setObjectName(QString::fromUtf8("btnGuest"));
        btnGuest->setGeometry(QRect(590, 320, 200, 150));
        btnGuest->setFont(font1);
        btnGuest->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        btnEnsure = new QPushButton(Widget);
        btnEnsure->setObjectName(QString::fromUtf8("btnEnsure"));
        btnEnsure->setGeometry(QRect(710, 30, 80, 50));
        btnEnsure->setStyleSheet(QString::fromUtf8("QPushButton\n"
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

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "      \345\260\217\345\214\272\351\227\250\347\246\201\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        btnUser->setText(QApplication::translate("Widget", "\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        btnGuest->setText(QApplication::translate("Widget", "\346\235\245\345\256\276", 0, QApplication::UnicodeUTF8));
        btnEnsure->setText(QApplication::translate("Widget", "\344\277\235\345\256\211\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
