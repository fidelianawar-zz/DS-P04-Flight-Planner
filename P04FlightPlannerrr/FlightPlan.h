
#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H

#include "AirportCity.h"
#include "DSAdjacencyList.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class FlightPlan {
    public:
        //FlightPlan(char*); //constructor to initialize adjacency list

        void readInputData(char*);
        void readRequestedFlights(char*, char*); //reads requested flight data

        DSVector<DSLinkedList<AirportCity>>& getAdjList();
        void printFlightData(); //prints out adjacency list

        void determinePath(AirportCity, DSString); //uses iterative backtracking to find paths
        void displayPath(ofstream&, char); //outputs paths to file

    private:
        DSVector<DSLinkedList<AirportCity>> adjacencyList; //contains data from undirected graph created by flight data file
        DSStack<AirportCity> flightPath;
        DSVector<DSStack<AirportCity>> totalPaths; //contains all possible paths for a requested flight
};

#endif // FLIGHTPLAN_H
