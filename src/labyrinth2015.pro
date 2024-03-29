######################################################################
# Automatically generated by qmake (3.0) ne kv? 10 19:26:57 2015
######################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labyrinth2015
TEMPLATE = app
INCLUDEPATH += .
QMAKE_CXXFLAGS += -std=c++11

# Input
HEADERS += boardfield.h \
           card.h \
           clienthandler.h \
           constants.h \
           controller.h \
           deck.h \
           field_const.h \
           game.h \
           gameboard.h \
           gamefield.h \
           gameitem.h \
           gameobject.h \
           gameover.h \
           iboardfield.h \
           lboardfield.h \
           loaddialog.h \
           menu.h \
           namesdialogue.h \
           pixmap_ops.h \
           player.h \
           savedialogue.h \
           startdialogue.h \
           strings.h \
           tboardfield.h \
           ui_gameover.h \
           ui_loaddialog.h \
           ui_menu.h \
           ui_namesdialogue.h \
           ui_savedialogue.h \
           ui_startdialogue.h \
           ui_widget.h \
           viewer.h \
           viewercli.h \
           widget.h
           
FORMS += gameover.ui \
         loaddialog.ui \
         menu.ui \
         namesdialogue.ui \
         savedialogue.ui \
         startdialogue.ui \
         widget.ui
         
SOURCES += boardfield.cpp \
           card.cpp \
           clienthandler.cpp \
           controller.cpp \
           deck.cpp \
           field_const.cpp \
           game.cpp \
           gameboard.cpp \
           gamefield.cpp \
           gameitem.cpp \
           gameobject.cpp \
           gameover.cpp \
           iboardfield.cpp \
           lboardfield.cpp \
           loaddialog.cpp \
           main.cpp \
           menu.cpp \
           namesdialogue.cpp \
           pixmap_ops.cpp \
           player.cpp \
           savedialogue.cpp \
           startdialogue.cpp \
           tboardfield.cpp \
           viewer.cpp \
           viewercli.cpp \
           widget.cpp
