QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    card.cpp \
    deck.cpp \
    hand.cpp \
    info.cpp \
    main.cpp \
    mainwindow.cpp \
    namewindow.cpp \
    playwindow.cpp \
    rules.cpp \
    scene.cpp \
    score.cpp \
    table.cpp

HEADERS += \
    button.h \
    card.h \
    deck.h \
    hand.h \
    info.h \
    mainwindow.h \
    namewindow.h \
    playwindow.h \
    rules.h \
    scene.h \
    score.h \
    table.h

FORMS += \
    mainwindow.ui \
    namewindow.ui \
    playwindow.ui \
    rules.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    resources.qrc

