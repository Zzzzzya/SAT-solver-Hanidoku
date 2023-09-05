QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hanidoku_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    num_change.cpp \
    sat_widget.cpp

HEADERS += \
    Hanidoku.h \
    SAT_solve_yh.h \
    hanidoku_widget.h \
    mainwindow.h \
    num_change.h \
    sat_widget.h \
    type.h

FORMS += \
    hanidoku_widget.ui \
    mainwindow.ui \
    num_change.ui \
    sat_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resource/picture/hexagon_1.png

RESOURCES += \
    cnf.qrc \
    pic.qrc
