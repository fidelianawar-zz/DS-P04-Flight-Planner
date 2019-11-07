TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        AdjacencyList.cpp \
        AirportCity.cpp \
        DSString.cpp \
        FlightPlan.cpp \
        main.cpp \
        tests.cpp

HEADERS += \
    AdjacencyList.h \
    AirportCity.h \
    DSAdjacencyList.h \
    DSLinkedList.h \
    DSNode.h \
    DSStack.h \
    DSString.h \
    DSVector.h \
    FlightPlan.h \
    catch.hpp

DISTFILES += \
    ../build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/flightDataInput.txt \
    ../build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/output.txt \
    ../build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/requestedFlightPath.txt
