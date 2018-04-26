#-------------------------------------------------
#
# Project created by QtCreator 2018-02-26T20:56:38
#
#-------------------------------------------------

QT       += core gui
QT  +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpServer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    form.cpp

HEADERS  += widget.h \
    form.h

FORMS    += widget.ui \
    form.ui

RESOURCES += \
    img.qrc
