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
    chart.cpp \
    controler.cpp \
    decodethread.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mylcdnumber.cpp \
    newtestwidget.cpp \
    systemsetwidget.cpp \
    tcpclient.cpp \
    tcpconnectwidget.cpp \
    testwidget.cpp \
    worker.cpp

HEADERS += \
    chart.h \
    commandList.h \
    controler.h \
    decodethread.h \
    includeHeader.h \
    loginwidget.h \
    mainwindow.h \
    mylcdnumber.h \
    newtestwidget.h \
    systemsetwidget.h \
    tcpclient.h \
    tcpconnectwidget.h \
    testwidget.h \
    worker.h

FORMS += \
    loginwidget.ui \
    mainwindow.ui \
    newtestwidget.ui \
    systemsetwidget.ui \
    tcpconnectwidget.ui \
    testwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
