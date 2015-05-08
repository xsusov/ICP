#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T00:21:49
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbtest
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        widget.cpp \
    pixmap_ops.cpp \
    field_const.cpp \
    menu.cpp

HEADERS  += widget.h \
    field_const.h \
    pixmap_ops.h \
    menu.h

FORMS    += widget.ui \
    menu.ui
