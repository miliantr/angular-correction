TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/ballistics/atm.cpp \
        src/ballistics/ball.cpp \
        src/ballistics/erath_model.cpp \
        src/math/linal.cpp

DISTFILES += \
    src/ballistics/.gitkeep \
    utils/.gitkeep \
    utils/.txt

HEADERS += \
    src/ballistics/atm.h \
    src/ballistics/ball.h \
    src/ballistics/const.h \
    src/ballistics/erath_model.h \
    src/math/linal.h
