TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DSString.cpp \
        main.cpp \
        tests.cpp

HEADERS += \
    DSAdjacencyList.h \
    DSLinkedList.h \
    DSNode.h \
    DSStack.h \
    DSString.h \
    DSVector.h \
    catch.hpp
