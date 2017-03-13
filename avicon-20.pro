#-------------------------------------------------
#
# Project created by QtCreator 2017-02-06T13:55:34
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG(testconf) {
    message(Test configuration)
    include(tests/tests.pro)
} else {
    message(Default configuration)
    SOURCES += main.cpp
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
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

include(./version/version.pri)

SOURCES += core.cpp \
    device/device.cpp \
    device/spi/driverspi.cpp \
    device/devicestate.cpp \
    ui/ascanwidget.cpp \
    ui/controls/touchspinbox.cpp \
    ui/controlpanel.cpp \
    device/modificators/modificator.cpp \
    ui/statusbar.cpp \
    device/spi/fakespi.cpp \
    ui/bscanwidget.cpp \
    ui/channelselector.cpp \
    ui/controls/channelbutton.cpp \
    device/tact/tact.cpp \
    ui/bscanpage.cpp \
    ui/ascanpage.cpp \
    ui/menupanel.cpp \
    ui/bscanwidgetopengl.cpp \
    device/modificators/gatemodificator.cpp \
    ui/controls/gatecontroller.cpp \
    ui/controls/addgatebutton.cpp \
    ui/controls/iconwidget.cpp \
    device/modificators/addgatemodificator.cpp \
    device/modificators/removegatemodificator.cpp \
    ui/controls/touchspinboxstring.cpp \
    ui/channelsview.cpp \
    ui/mainwindow.cpp \
    ui/helpwidget.cpp \
    ui/modeselectionwidget.cpp \
    ui/registrationwidget.cpp \
    ui/memorywidget.cpp \
    ui/optionswidget.cpp \
    ui/systemwidget.cpp \
    ui/tvgeditorwidget.cpp \
    ui/ascaninfowidget.cpp \
    system/system.cpp \
    system/filesystem.cpp \
    device/channel/rxchannel.cpp \
    device/channel/txchannel.cpp \
    device/channel/channel.cpp \
    device/tvg/tvgcurve.cpp \
    device/tvg/tvgsinglepoint.cpp \
    device/tact/tacttable.cpp \
    device/modificators/prismtimemodificator.cpp \
    device/channelscalibration.cpp \
    device/devicemode.cpp \
    device/modemanager.cpp \
    ui/controls/modeselectionbutton.cpp \
    ui/controls/schemeselectionbutton.cpp \
    device/calibrationmanager.cpp \
    ui/calibrationswidget.cpp \
    device/modificators/tvgmodificator.cpp \
    ui/controls/calibrationbutton.cpp \
    device/channel/displaychannel.cpp \
    system/brightnesscontroller.cpp \
    system/temperature.cpp \
    system/sound.cpp \
    system/batterycontroller.cpp \
    system/datetimecontroller.cpp
#    tests/coretest.cpp

HEADERS  += \
    core.h \
    device/device.h \
    device/spi/driverspi.h \
    device/definitions.h \
    device/devicestate.h \
    ui/ascanwidget.h \
    ui/controls/touchspinbox.h \
    ui/controlpanel.h \
    device/modificators/modificator.h \
    ui/statusbar.h \
    device/spi/deviceinterface.h \
    device/spi/fakespi.h \
    ui/bscanwidget.h \
    ui/channelselector.h \
    ui/controls/channelbutton.h \
    device/tact/tact.h \
    ui/bscanpage.h \
    ui/ascanpage.h \
    ui/menupanel.h \
    ui/bscanwidgetopengl.h \
    device/modificators/gatemodificator.h \
    ui/controls/gatecontroller.h \
    ui/controls/addgatebutton.h \
    ui/controls/iconwidget.h \
    device/modificators/addgatemodificator.h \
    device/modificators/removegatemodificator.h \
    ui/controls/touchspinboxstring.h \
    ui/channelsview.h \
    ui/mainwindow.h \
    ui/helpwidget.h \
    ui/modeselectionwidget.h \
    ui/registrationwidget.h \
    ui/memorywidget.h \
    ui/optionswidget.h \
    ui/systemwidget.h \
    ui/tvgeditorwidget.h \
    ui/ascaninfowidget.h \
    system/system.h \
    system/filesystem.h \
    device/channel/rxchannel.h \
    device/channel/txchannel.h \
    device/channel/channel.h \
    device/tvg/tvgcurve.h \
    device/tvg/tvgsinglepoint.h \
    device/tact/tacttable.h \
    device/modificators/prismtimemodificator.h \
    device/channelscalibration.h \
    device/devicemode.h \
    device/modemanager.h \
    ui/controls/modeselectionbutton.h \
    ui/controls/schemeselectionbutton.h \
    device/calibrationmanager.h \
    device/tactid.h \
    ui/calibrationswidget.h \
    device/modificators/tvgmodificator.h \
    ui/controls/calibrationbutton.h \
    device/commonfunctions.h \
    device/channel/displaychannel.h \
    system/brightnesscontroller.h \
    system/temperature.h \
    system/sound.h \
    system/batterycontroller.h \
    system/datetimecontroller.h
#    tests/coretest.h

FORMS    += \
    ui/ascanwidget.ui \
    ui/controls/touchspinbox.ui \
    ui/controlpanel.ui \
    ui/statusbar.ui \
    ui/bscanwidget.ui \
    ui/channelselector.ui \
    ui/controls/channelbutton.ui \
    ui/bscanpage.ui \
    ui/ascanpage.ui \
    ui/menupanel.ui \
    ui/bscanwidgetopengl.ui \
    ui/controls/gatecontroller.ui \
    ui/controls/addgatebutton.ui \
    ui/controls/iconwidget.ui \
    ui/controls/touchspinboxstring.ui \
    ui/channelsview.ui \
    ui/mainwindow.ui \
    ui/helpwidget.ui \
    ui/modeselectionwidget.ui \
    ui/registrationwidget.ui \
    ui/memorywidget.ui \
    ui/optionswidget.ui \
    ui/systemwidget.ui \
    ui/tvgeditorwidget.ui \
    ui/ascaninfowidget.ui \
    ui/controls/modeselectionbutton.ui \
    ui/controls/schemeselectionbutton.ui \
    ui/calibrationswidget.ui \
    ui/controls/calibrationbutton.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    style.astylerc
