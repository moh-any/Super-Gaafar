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
<<<<<<< HEAD
    player.cpp \
=======
    platform.cpp \
    player.cpp \
    pole.cpp \
//>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703
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
<<<<<<< HEAD
    player.h \
=======
    platform.h \
    player.h \
    pole.h \
//>>>>>>> efe10f60e5238827d4b4fada4d846132ba7b4703
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
