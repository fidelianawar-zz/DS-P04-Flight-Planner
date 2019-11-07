#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H

#include "AirportCity.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>

using namespace std;

class FlightPlan {
public:
    FlightPlan();
    FlightPlan(char*); //constructor to initialize adjacency list
    void addAirport(DSString, DSString, double, int); //add arrival node to linkedlist
    int departureExists(DSString);
    bool arrivalExists(DSString, int);
    void readRequestedFlights(char*, char*); //reads requested flight data
    void readFlightData(char*,char*,char*);

    DSVector<DSLinkedList<AirportCity>>& getAdjList();
    void printFlightData(); //prints out adjacency list

    void findPaths(AirportCity, DSString); //uses iterative backtracking to find paths
    void outputPaths(ofstream&, char); //outputs paths to file

private:
    DSVector<DSLinkedList<AirportCity>> adjList; //contains data from undirected graph created by flight data file
    DSStack<AirportCity> path;
    DSVector<DSStack<AirportCity>> allPaths; //contains all possible paths for a requested flight
};

#endif // FLIGHTPLAN_H
