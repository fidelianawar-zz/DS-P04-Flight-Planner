#include "FlightPlan.h"
#include "AirportCity.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include "DSAdjacencyList.h"

DSAdjacencyList flightlist;

//reads in flight input and initializes adjacency list
void FlightPlan::readInputData(char* flightInputData) {

    ifstream inputFile;
    int numberOfFlights;
    char departureCity[50];
    char arrivalCity[50];
    char airlineName[50];
    double cost;
    int time;

    inputFile.open(flightInputData);

    if (!inputFile) {
        cerr << "Cannot open flight data file" << endl;
        exit(EXIT_FAILURE);
    }

    inputFile >> numberOfFlights;
    inputFile.ignore();

    inputFile.getline(departureCity, 50, '|');

    while (!inputFile.eof()) {
        inputFile.getline(arrivalCity, 50, '|');
        inputFile >> cost;
        inputFile.ignore();
        inputFile >> time;
        inputFile.ignore();
        inputFile >> airlineName;
        inputFile.ignore();

        //create DSString objects from character buffers
        DSString departure(departureCity);
        DSString arrival(arrivalCity);
        DSString airline(airlineName);

        //add departure/arrival node with all respective necessary information
        flightlist.addNode(departure, arrival, cost, time, airline);
        flightlist.addNode(arrival, departure, cost, time, airline);

        inputFile.getline(departureCity, 50, '|');
    }
    inputFile.close();

}

//reads in requested flight data and calls functions to find possible paths and output them
void FlightPlan::readRequestedFlights(char* requestedFlights, char* outputFile) {

    ifstream requestedFlightInput;
    ofstream outfile;

    char departureCity[90];
    char arrivalCity[90];
    char requestedInput;
    int currFlight = 0;
    int numberOfFlights;

    adjacencyList = flightlist.getAdjList();

    requestedFlightInput.open(requestedFlights);
    if (!requestedFlightInput) {
        cerr << "Cannot open requested file data" << endl;
        exit(EXIT_FAILURE);
    }

    outfile.open(outputFile);
    if (!outfile) {
        cerr << "Cannot open output file" << endl;
        exit(EXIT_FAILURE);
    }

    requestedFlightInput >> numberOfFlights; //reads in number of flights requested
    requestedFlightInput.ignore();

    requestedFlightInput.getline(departureCity, 50, '|'); //read in requested departure location name

    while (!requestedFlightInput.eof()) {

        currFlight++;

        requestedFlightInput.getline(arrivalCity, 50, '|'); //read in requested arrival location name
        requestedFlightInput >> requestedInput; //read in cost or time as parameter for ordering output
        requestedFlightInput.ignore();

        DSString departure(departureCity);
        DSString arrival(arrivalCity);

        //print flight header
        outfile << "Flight " << currFlight << ": ";
        outfile << departure<< ", " << arrival << " ";
        outfile << "(";

        if (requestedInput == 'C') {
            outfile << "Cost)" << endl;
        }

        else if (requestedInput == 'T') {
            outfile << "Time)" << endl;
        }

        //checks to see if departure/arrival cities already exist in adjacency list or not
        bool departureExists = false;
        bool arrivalExists = false;
        for (int i = 0; i < adjacencyList.getSize(); i++) {
            for (int j = 0; j < adjacencyList[i].size(); j++) {
                if (adjacencyList[i].get(0).getName() == departure) {
                    departureExists = true;
                }
                if (adjacencyList[i].get(0).getName() == arrival) {
                    arrivalExists = true;
                }
            }
        }

        if (departureExists == false && arrivalExists == false) {
            outfile << "Departure and arrival locations are not found" << endl << endl;
        }
        else if (arrivalExists == false){
            outfile << "Arrival location is not found" << endl << endl;
        }
        else if (departureExists == false){
            outfile << "Departure locationis not found" << endl << endl;
        }
        else {
            if (!(departure == arrival)) {
                int location;
                for (int i = 0; i < adjacencyList.getSize(); i++) {
                    if (adjacencyList[i].get(0).getName() == departure) {
                        location = i;
                    }
                }
                determinePath(adjacencyList[location].get(0), arrival);
                displayPath(outfile, requestedInput);
            }
            else {
                outfile << "Same city flight not found" << endl;
            }
        }
        requestedFlightInput.getline(departureCity, 50, '|');
    }
    requestedFlightInput.close();
    outfile.close();
}


//use iterative backtracking
void FlightPlan::determinePath(AirportCity a, DSString b) {

    int locationIndex;
    flightPath.push(a);

    //resets iterator to first arrival node
    for (int i = 0; i < adjacencyList.getSize(); i++) {
        adjacencyList[i].backtrack();
    }

    //search for all possible paths until empty
    while (!flightPath.isEmpty()) {
        AirportCity temp = flightPath.peek(); //most recently visited
        for (int i = 0; i < adjacencyList.getSize(); i++) {
            if (adjacencyList[i].get(0).getName() == temp.getName()) {
                locationIndex = i;
            }
        }

        if (adjacencyList[locationIndex].hasNext()) { //has iterator has reached end of LL
            AirportCity next = adjacencyList[locationIndex].getNext();
            if (!flightPath.contains(next)) { //is airport is already in the path
                flightPath.push(next);
                if (flightPath.peek().getName() == b) { //is most recent airport is destination
                    totalPaths.push_back(flightPath);
                    flightPath.pop();
                }
            }
        }
        else {
            adjacencyList[locationIndex].resetIterator(); //iterator is reset to head
            adjacencyList[locationIndex].backtrack(); //move iterator to first arrival node
            flightPath.pop();
        }
    }
}

void FlightPlan::calculateCost(ofstream& outFile){

    double layoverCost = 0.0;
    int layoverTime = 0;
    int pathNumber = 0;
    double recentLowest = 0;

    for (int i = 0; i < 3; i++) { //only iterate 3 times
        if (i > totalPaths.getSize()-1) { //if paths number < 3, stop
            break;
        }
        pathNumber++;
        int index = -1; //index of path with lowest cost
        double cheapest = 20000;
        for (int i = 0; i < totalPaths.getSize(); i++) {
            double currCost = 0;
            for (int j = 0; j < totalPaths[i].size(); j++) {
                currCost += totalPaths[i].get(j).getCost(); //calculates cost of current path
            }

            //sets currCost as lowest it is lower than prev
            if (currCost < cheapest && currCost > recentLowest) {
                cheapest = currCost;
                index = i;
            }
        }

        recentLowest = cheapest;

        double totalCost = cheapest;
        int totalTime = 0;

        for (int i = 0; i < totalPaths[index].size(); i++) {

            //output name of airport
            outFile << totalPaths[index].get(i).getName();

            //checks to see if first departure node or not
            if(totalPaths[index].get(i).getAirline() == ""){

            }
            else{
                outFile << " (" << totalPaths[index].get(i).getAirline() << ")";
            }
            if(i == totalPaths[index].size()-1){
                outFile << ". ";

            }
            else{
                outFile << " -> ";
                //if it is not direct flight (more than 2 nodes), do this
                if((totalPaths[index].size() > 2)){
                    //if airline names don't match, 65 min time incr
                    if(!(totalPaths[index].get(i).getAirline() == totalPaths[index].get(i+1).getAirline())){
                        layoverCost += 19;
                        layoverTime += 65;
                    }
                }
            }
            totalTime += totalPaths[index].get(i).getTime();
        }

        //make sure the end destination node does not get extra time/cost added onto it
        if(totalPaths[index].size() > 2){
            layoverCost -= 19;
            layoverTime -= 43;
        }

        outFile << "Time: " << totalTime + layoverTime<< " "; //outputs total time
        outFile << "Cost: " << fixed << setprecision(2) << totalCost + layoverCost << endl; //outputs total cost
    }

}

void FlightPlan::calculateTime(ofstream& outFile)
{
    int pathNumber = 0;
    int recentLowest = 0; //track most recen time
    double layoverCost = 0.0;
    int layoverTime = 0;

    for (int i = 0; i < 3; i++) {
        if (i > totalPaths.getSize()-1) {
            break;
        }
        pathNumber++;
        int index = -1; //path with lowest time
        int fastest = 2000;
        for (int i = 0; i < totalPaths.getSize(); i++) {
            int currTime = 0;
            for (int j = 0; j < totalPaths[i].size(); j++) {
                currTime += totalPaths[i].get(j).getTime(); //calculates total time of current path
            }

            //sets currTime as fastest if faster tha nprev
            if (currTime < fastest && currTime > recentLowest) {
                fastest = currTime;
                index = i;
            }
        }

        recentLowest = fastest;

        int totalTime = fastest;
        double totalCost = 0;

        //outputs formatted path
        outFile << "Path " << pathNumber << ": ";

        for (int i = 0; i < totalPaths[index].size(); i++) { //outputs each airport in path
            outFile << totalPaths[index].get(i).getName();

            if(totalPaths[index].get(i).getAirline() == ""){

            }
            else{
                outFile << " (" << totalPaths[index].get(i).getAirline() << ")";
            }
            if(i == totalPaths[index].size()-1){
                outFile << ". ";

            }
            else{
                outFile << " -> ";
                if((totalPaths[index].size() > 2)){
                    if(!(totalPaths[index].get(i).getAirline() == totalPaths[index].get(i+1).getAirline())){
                        layoverCost += 19;
                        layoverTime += 65;
                    }
                }
            }
            totalCost += totalPaths[index].get(i).getCost();
        }
        if(totalPaths[index].size() > 2){
            layoverCost -= 19;
            layoverTime -= 43;
        }
        outFile << "Time: " << totalTime + layoverTime << " "; //outputs total time
        outFile << "Cost: " << fixed << setprecision(2) << totalCost + layoverCost<< endl; //outputs total cost
    }

    outFile << endl;
}

//prints to output file best 3 paths or error if no paths
void FlightPlan::displayPath(ofstream& outFile, char requestedInput) {

    //if no paths were found
    if (totalPaths.empty() == true) {
        outFile << "No paths could be found." << endl << endl;
    }
    else {
        if (requestedInput == 'C') { //cost order
            calculateCost(outFile);

        }
        else if (requestedInput == 'T') { //if ordering by time
            calculateTime(outFile);
        }

        //remove paths to move onto next flight
        while (totalPaths.empty() == false) {
            totalPaths.pop_back();
        }
    }
}

