#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "AirportCity.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include "FlightPlan.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class AdjacencyList {
    public:
        AdjacencyList(); //constructor to initialize adjacency list
        void addAirport(DSString, DSString, double, int, DSString); //add arrival node to linkedlist
        int departureExists(DSString);
        bool arrivalExists(DSString, int, DSString);
        void readRequestedFlights(char*, char*); //reads requested flight data

        DSVector<DSLinkedList<AirportCity>>& getAdjList();
        void printFlightData(); //prints out adjacency list

        void findPaths(AirportCity, DSString); //uses iterative backtracking to find paths
        void outputPaths(ofstream&, char); //outputs paths to file

    private:
        DSVector<DSLinkedList<AirportCity>> adjacencyList; //contains data from undirected graph created by flight data file
        DSStack<AirportCity> path;
        DSVector<DSStack<AirportCity>> allPaths; //contains all possible paths for a requested flight
};

#endif // ADJACENCYLIST_H
