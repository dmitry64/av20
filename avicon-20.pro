#-------------------------------------------------
#
# Project created by QtCreator 2017-02-06T13:55:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = avicon-20
TEMPLATE = app

#QMAKE_CXXFLAGS_DEBUG *= -pg
#QMAKE_LFLAGS_DEBUG *= -pg

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

target.path = /home/root
INSTALLS += target

SOURCES += main.cpp\
        debuggui.cpp \
    core.cpp \
    device/device.cpp \
    device/spi/driverspi.cpp \
    device/devicestate.cpp \
    ui/ascanwidget.cpp \
    ui/controls/touchspinbox.cpp \
    ui/controlpanel.cpp \
    device/modificators/modificator.cpp \
    device/modificators/tvgsimplemodificator.cpp \
    device/devicecalibration.cpp \
    ui/statusbar.cpp \
    device/spi/fakespi.cpp \
    ui/bscanwidget.cpp \
    ui/channelselector.cpp \
    ui/controls/channelbutton.cpp \
    device/modificators/activechannelmodificator.cpp \
    device/tact.cpp \
    device/channel.cpp \
    ui/bscanpage.cpp \
    ui/ascanpage.cpp \
    ui/menupanel.cpp

HEADERS  += debuggui.h \
    core.h \
    device/device.h \
    device/spi/driverspi.h \
    device/definitions.h \
    device/devicestate.h \
    ui/ascanwidget.h \
    ui/controls/touchspinbox.h \
    ui/controlpanel.h \
    device/modificators/modificator.h \
    device/modificators/tvgsimplemodificator.h \
    device/devicecalibration.h \
    ui/statusbar.h \
    device/spi/deviceinterface.h \
    device/spi/fakespi.h \
    ui/bscanwidget.h \
    ui/channelselector.h \
    ui/controls/channelbutton.h \
    device/modificators/activechannelmodificator.h \
    device/tact.h \
    device/channel.h \
    ui/bscanpage.h \
    ui/ascanpage.h \
    ui/menupanel.h

FORMS    += debuggui.ui \
    ui/ascanwidget.ui \
    ui/controls/touchspinbox.ui \
    ui/controlpanel.ui \
    ui/statusbar.ui \
    ui/bscanwidget.ui \
    ui/channelselector.ui \
    ui/controls/channelbutton.ui \
    ui/bscanpage.ui \
    ui/ascanpage.ui \
    ui/menupanel.ui

RESOURCES += \
    resources.qrc
