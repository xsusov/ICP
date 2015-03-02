TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    server.cpp

include(deployment.pri)
qtcAddDeployment()

