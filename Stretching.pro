QT       += core gui
QT       += network
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS+=$$PWD/libs/libcomponents.a
INCLUDEPATH+=$$PWD/libs/Include

SOURCES += \
    decodethread.cpp \
    main.cpp \
    mainwindow.cpp \
    motor.cpp \
    tcpclient.cpp \
    testwidget.cpp

HEADERS += \
    decodethread.h \
    includeHeader.h \
    mainwindow.h \
    motor.h \
    tcpclient.h \
    testwidget.h

FORMS += \
    mainwindow.ui \
    testwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
