TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../P04FlightPlanner/AirportCity.cpp \
        ../P04FlightPlanner/DSAdjacencyList.cpp \
        ../P04FlightPlanner/DSString.cpp \
        ../P04FlightPlanner/FlightPlan.cpp \
        ../P04FlightPlanner/main.cpp

HEADERS += \
    ../P04FlightPlanner/AirportCity.h \
    ../P04FlightPlanner/DSAdjacencyList.h \
    ../P04FlightPlanner/DSLinkedList.h \
    ../P04FlightPlanner/DSStack.h \
    ../P04FlightPlanner/DSString.h \
    ../P04FlightPlanner/DSVector.h \
    ../P04FlightPlanner/FlightPlan.h \
    ../P04FlightPlanner/catch.hpp

DISTFILES += \
    flightInputData.txt \
    flightPathRequest.txt
