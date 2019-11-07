#include "AirportCity.h"
#include "AdjacencyList.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include <fstream>
#include <iostream>

AdjacencyList::AdjacencyList(){

}
//getter for adjacency list
DSVector<DSLinkedList<AirportCity>>& AdjacencyList::getAdjList() {
    return adjacencyList;
}

//adds a connection to the adjacency list, either as a departure node or arrival node
void AdjacencyList::addAirport(DSString departureCity, DSString arrivalCity, double cost, int time, DSString airline) {
    int location = departureExists(departureCity); //checks to see if departure node already exists
    if (location == -1) { //if departure node does not exist
        AirportCity newOrigin(departureCity); //create a departure node with cost and time as zero
        DSLinkedList<AirportCity> newList(newOrigin); //create linkedlist with departure node as head
        AirportCity dest(arrivalCity, cost, time, airline); //create arrival node with associated cost and time
        newList.insertEnd(dest); //add to linkedlist with connected departure node
        adjacencyList.push_back(newList); //add to adjacency list
       // adjacencyList.printVector();
        //cout << adjacencyList.getSize() << endl;
    }
    else { //departure node already exists
        bool arrival = arrivalExists(arrivalCity, location, airline); //checks to see if arrival node exists in departure linkedlist
        if (arrival == false) {
            AirportCity dest(arrivalCity, cost, time, airline); //create new arrival node with associated cost and time
            adjacencyList[location].insertEnd(dest); //add to existing departure linkedlist in adjacency list
        }
    }
}

//checks to see if departure node already exists in adjacency list
int AdjacencyList::departureExists(DSString city) {
    int indexLoc = -1;
    for (int i = 0; i < adjacencyList.getSize(); i++) {
        //if there is a departure node as head of linkedlist with the same name as parameter
        if (adjacencyList[i].get(0).getName() == city) {
            indexLoc = i;
            return indexLoc;
        }
    }
    return indexLoc;
}

//checks to see if arrival node already exists in departure linkedlist
bool AdjacencyList::arrivalExists(DSString city, int locationIndex, DSString airline) {
    for (int i = 0; i < adjacencyList[locationIndex].getSize(); i++) {
        //if there is an arrival node in departure linkedlist with the same name as parameter
        if (adjacencyList[locationIndex][i].getName() == city && adjacencyList[locationIndex][i].getAirline() == airline) {
            if(adjacencyList[i].get(0).getName() == city && !(adjacencyList[i].get(0).getAirline() == airline)){
                adjacencyList[i].get(0).setAirline(airline);
                return true;
            }
            return true;
        }
    }
    return false;
}

//function used to test reading in of all data to adjacency list
void AdjacencyList::printFlightData() {

    for (int i = 0; i < adjacencyList.getSize(); i++) { //for every linkedlist in adjList
        for (int j = 0; j < adjacencyList[i].getSize(); j++) { //for every Airport node in associated linkedlist

            cout<<adjacencyList[i][j].getName(); //prints out Airport data

            if(adjacencyList[i][j].getAirline() == ""){
            }
            else{
                cout << "(" << adjacencyList[i][j].getAirline() <<  ")";
            }
            if(j == adjacencyList.getSize() - 1){
                cout << endl;
            }
            else{
                cout << " -> ";
            }
        }
        //cout << endl;
    }
}
