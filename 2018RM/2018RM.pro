TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    getfile.cpp \
    SaveDepth.cpp \
    findtarget.cpp
LIBS += /usr/local/opencv2/lib/libopencv*
LIBS += /usr/local/zed/lib/*
LIBS += /usr/local/cuda-10.0/lib64/lib*
HEADERS += \
    getfile.h \
    SaveDepth.hpp \
    findtarget.h
INCLUDEPATH +=/usr/local/zed/include
INCLUDEPATH +=/usr/local/cuda-10.0/include
DEFINES += QT_NO_WARNING_OUTPUT\
                     QT_NO_DEBUG_OUTPUT
