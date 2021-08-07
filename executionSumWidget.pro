QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += shared

TEMPLATE = lib
DESTDIR = /home/semen/qtProjects/test

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    executionsumwidget.cpp \
    formats.cpp \
    md5sum.cpp \
    readdirectory.cpp

HEADERS += \
    ../AbstractClasses/abstractclasses.h \
    executionsumwidget.h \
    formats.h \
    md5sum.h \
    readdirectory.h

LIBS += -lboost_filesystem
LIBS += -lboost_system

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
