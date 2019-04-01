TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    getfile.cpp
LIBS += /usr/local/lib/libopencv_*

HEADERS += \
    getfile.h
