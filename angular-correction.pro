TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/math/linal.cpp

DISTFILES += \
    src/ballistics/.gitkeep \
    utils/.gitkeep \
    utils/.txt

HEADERS += \
    src/ballistics/const.h \
    src/math/linal.h
