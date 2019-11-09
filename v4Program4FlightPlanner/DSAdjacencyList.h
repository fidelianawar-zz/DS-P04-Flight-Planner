#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "AirportCity.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class DSAdjacencyList {
    public:
        DSAdjacencyList();
        void addNode(DSString, DSString, double, int, DSString);  //add arrival node
        int departureExists(DSString); //gets position of departure (head) node
        bool arrivalExists(DSString, int, DSString); //returns T/F if arrival is in path or not

        DSVector<DSLinkedList<AirportCity>>& getAdjList();
        void printFlightData();

    private:
        DSVector<DSLinkedList<AirportCity>> DSadjacencyList;
        DSStack<AirportCity> path;
        DSVector<DSStack<AirportCity>> allPaths; // all possible paths for a requested flight
};

#endif // ADJACENCYLIST_H
