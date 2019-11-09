TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        AirportCity.cpp \
        DSAdjacencyList.cpp \
        DSString.cpp \
        FlightPlan.cpp \
        main.cpp

HEADERS += \
    ../../Downloads/catch.hpp \
    AirportCity.h \
    DSAdjacencyList.h \
    DSLinkedList.h \
    DSStack.h \
    DSString.h \
    DSVector.h \
    FlightPlan.h

DISTFILES += \
    ../CSE2341-F19-Fidelia-Nawar/Sprint4/build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/flightDataInput.txt \
    ../CSE2341-F19-Fidelia-Nawar/Sprint4/build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/output.txt \
    ../CSE2341-F19-Fidelia-Nawar/Sprint4/build-Program4-Desktop_Qt_5_10_0_GCC_64bit-Debug/requestedFlightPath.txt
