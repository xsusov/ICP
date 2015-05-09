#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T00:21:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbtest
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        widget.cpp \
    pixmap_ops.cpp \
    field_const.cpp \
    menu.cpp \
    player.cpp \
    card.cpp \
    gameobject.cpp \
    gameitem.cpp \
    boardfield.cpp \
    gameboard.cpp \
    deck.cpp \
    iboardfield.cpp \
    tboardfield.cpp \
    lboardfield.cpp \
    clienthandler.cpp \
    game.cpp \
    viewer.cpp \
    viewercli.cpp \
    controller.cpp \
    startdialogue.cpp \
    namesdialogue.cpp \
    savedialogue.cpp \
    loaddialog.cpp \
    gameover.cpp

HEADERS  += widget.h \
    field_const.h \
    pixmap_ops.h \
    menu.h \
    player.h \
    card.h \
    gameobject.h \
    gameitem.h \
    boardfield.h \
    gameboard.h \
    deck.h \
    iboardfield.h \
    tboardfield.h \
    lboardfield.h \
    constants.h \
    clienthandler.h \
    strings.h \
    game.h \
    viewer.h \
    viewercli.h \
    controller.h \
    startdialogue.h \
    namesdialogue.h \
    savedialogue.h \
    loaddialog.h \
    gameover.h

FORMS    += widget.ui \
    menu.ui \
    startdialogue.ui \
    namesdialogue.ui \
    savedialogue.ui \
    loaddialog.ui \
    gameover.ui
