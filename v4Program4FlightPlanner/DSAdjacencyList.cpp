#include "AirportCity.h"
#include "DSAdjacencyList.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>

DSAdjacencyList::DSAdjacencyList(){

}

//getter for adjacency list
DSVector<DSLinkedList<AirportCity>>& DSAdjacencyList::getAdjList() {
    return DSadjacencyList;
}

//adds a departure/arrival node to adj list
void DSAdjacencyList::addNode(DSString departure, DSString arrival, double cost, int time, DSString airline) {
    int indexLoc = departureExists(departure); //checks if departure node  exists
    if (indexLoc == -1) {
        AirportCity originalCity(departure); //create a departure node
        DSLinkedList<AirportCity> newList(originalCity); //LL of head nodes
        AirportCity destinationCity(arrival, cost, time, airline);
        newList.insert(destinationCity);
        DSadjacencyList.push_back(newList);
    }
    else { //departure node exists
        bool locExists = arrivalExists(arrival, indexLoc, airline); //checks if arrival node exists in departure LL
        if (locExists == false) {
            AirportCity dest(arrival, cost, time, airline);
            DSadjacencyList[indexLoc].insert(dest);
        }
    }
}

//checks if departure node exists in adjacency list
int DSAdjacencyList::departureExists(DSString city) {
    int indexLocation = -1;
    for (int i = 0; i < DSadjacencyList.getSize(); i++) {
        if (DSadjacencyList[i].get(0).getName() == city) {
            return i;
        }
    }
    return indexLocation;
}

//checks if arrival node exists in departure linkedlist and sets airline accordingly
bool DSAdjacencyList::arrivalExists(DSString city, int indexLocation, DSString airline) {
    for (int i = 0; i < DSadjacencyList[indexLocation].size(); i++) {
        if (DSadjacencyList[indexLocation][i].getName() == city && DSadjacencyList[indexLocation][i].getAirline() == airline) {
            if (DSadjacencyList[i].get(0).getName() == city && !(DSadjacencyList[i].get(0).getAirline() == airline)) {
                DSadjacencyList[i].get(0).setAirline(airline);
                return true;
            }
            return true;
        }
    }
    return false;
}

//test reading in of data in adjacency list
void DSAdjacencyList::printFlightData() {
    for (int i = 0; i < DSadjacencyList.getSize(); i++) {
        for (int j = 0; j < DSadjacencyList[i].size(); j++) {
            DSadjacencyList[i][j].print();
        }
        cout << endl;
    }
}
