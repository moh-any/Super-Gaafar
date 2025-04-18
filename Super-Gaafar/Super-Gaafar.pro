QT       += core gui
QT += core gui multimedia
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    castle.cpp \
    coin.cpp \
    enemy.cpp \
    flag.cpp \
    ground.cpp \
    main.cpp \
    maingamewindow.cpp \
    platform.cpp \
    player.cpp \
    pole.cpp \
    powerup.cpp
    coin.cpp
HEADERS += \
    background.h \
    castle.h \
    coin.h \
    enemy.h \
    flag.h \
    ground.h \
    maingamewindow.h \
    platform.h \
    player.h \
    pole.h \
    powerup.h
    coin.h

FORMS += \
    maingamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    coin.png
