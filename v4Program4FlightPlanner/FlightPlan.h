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
        void readInputData(char*); //reads all flight path input data
        void readRequestedFlights(char*, char*); //reads requested flight data

        DSVector<DSLinkedList<AirportCity>>& getAdjList(); //used to set adjlist equal to DSVec<DSLL<AirportCity>>
        void printFlightData(); //prints out adjacency list

        void calculateCost(ofstream&);
        void calculateTime(ofstream&);
        void outputData(ofstream&);

        void determinePath(AirportCity, DSString); //uses iterative backtracking to find paths
        void displayPath(ofstream&, char); //outputs paths to file

    private:
        DSVector<DSLinkedList<AirportCity>> adjacencyList;
        DSStack<AirportCity> flightPath;
        DSVector<DSStack<AirportCity>> totalPaths; //all possible paths for a requested flight


        int pathNumber = 0;
        double recentLowest = 0;

};

#endif // FLIGHTPLAN_H
