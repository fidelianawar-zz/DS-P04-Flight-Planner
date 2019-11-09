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
    AirportCity.h \
    DSAdjacencyList.h \
    DSLinkedList.h \
    DSStack.h \
    DSString.h \
    DSVector.h \
    FlightPlan.h \
    catch.hpp

DISTFILES += \
    ../build-v4Program4FlightPlanner-Desktop_Qt_5_10_0_GCC_64bit-Debug/v4FlightInputData.txt \
    ../build-v4Program4FlightPlanner-Desktop_Qt_5_10_0_GCC_64bit-Debug/v4FlightRequestedData.txt
