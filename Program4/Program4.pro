TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DSString.cpp \
        main.cpp \
        tests.cpp

HEADERS += \
    DSLinkedList.h \
    DSNode.h \
    DSString.h \
    DSVector.h \
    catch.hpp
