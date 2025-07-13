TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/ballistic.cpp \
        src/model.cpp \
        src/linal.cpp

DISTFILES += \
    src/ballistics/.gitkeep \
    utils/.gitkeep \
    utils/.txt

HEADERS += \
    src/ballistic.h \
    src/model.h \
    src/const.h \
    src/linal.h
