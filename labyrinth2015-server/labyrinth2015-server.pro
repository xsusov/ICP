TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    server.cpp \
    player.cpp \
    card.cpp \
    gameobject.cpp \
    gameitem.cpp \
    boardfield.cpp \
    gameboard.cpp \
    deck.cpp \
    playerfigure.cpp \
    iboardfield.cpp \
    tboardfield.cpp \
    lboardfield.cpp \
    clienthandler.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    player.h \
    card.h \
    gameobject.h \
    gameitem.h \
    boardfield.h \
    gameboard.h \
    deck.h \
    playerfigure.h \
    iboardfield.h \
    tboardfield.h \
    lboardfield.h \
    constants.h \
    clienthandler.h

