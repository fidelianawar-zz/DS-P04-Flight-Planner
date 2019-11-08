#include "FlightPlan.h"
#include "AirportCity.h"
#include "DSStack.h"
#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include "AdjacencyList.h"
AdjacencyList flightList;
FlightPlan::FlightPlan(){}
void FlightPlan::readFlightData(char* flightData, char* f2, char*f3) {

    ifstream inFile;
    inFile.open(flightData, ios::in);

    if (!inFile) {
        cerr << "Flight data file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    int numConnections;
    inFile >> numConnections; //read in number of connections between different cities
    inFile.ignore();
    char depart[81];
    char arrive[81];
    double cost;
    char airlineName[81];
    int time;

    inFile.getline(depart, 81, '|'); //get departure city

    while (!inFile.eof()) {
        inFile.getline(arrive, 81, '|'); //get arrival city
        inFile >> cost; //get cost associated
        inFile.ignore();
        inFile >> time; //get time associated
        inFile.ignore();
        inFile >> airlineName; //get time associated
        inFile.ignore();

        //create String objects from char arrays
        DSString departure(depart);
        DSString arrival(arrive);
        DSString airline(airlineName);


        //add Airport data both directions
        flightList.addAirport(departure, arrival, cost, time, airline);
        flightList.addAirport(arrival, departure, cost, time, airline);

        //printFlightData();

        flightList.printFlightData();

        inFile.getline(depart, 81, '|'); //get next connection
    }
    inFile.close();

    readRequestedFlights(f2, f3);
}

//reads in requested flight data and calls functions to find possible paths and output them
void FlightPlan::readRequestedFlights(char* requestedFlights, char* outputFile) {

    adjList = flightList.getAdjList();

    ifstream inFile;
    inFile.open(requestedFlights, ios::in);
    if (!inFile) {
        cerr << "Requested flight file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    ofstream outFile;
    outFile.open(outputFile, ios::out);
    if (!outFile) {
        cerr << "Output file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    int numFlights;
    inFile >> numFlights; //reads in number of flights requested
    inFile.ignore();
    char depart[81];
    char arrive[81];
    char metric;

    int currentFlight = 0;

    inFile.getline(depart, 81, '|'); //read in requested departure location name

    while (!inFile.eof()) {
        currentFlight++;

        inFile.getline(arrive, 81, '|'); //read in requested arrival location name
        inFile >> metric; //read in cost or time as parameter for ordering output
        inFile.ignore();

        DSString departure(depart);
        DSString arrival(arrive);

        //print flight header
        outFile << "Flight " << currentFlight << ": ";
        outFile << departure.c_str() << ", " << arrival.c_str() << " ";
        outFile << "(";

        if (metric == 'T') {
            outFile << "Time)" << endl;
        }
        else if (metric == 'C') {
            outFile << "Cost)" << endl;
        }

        //checks to see if departure and arrival cities exist in adjList
        bool departExists = false;
        bool arriveExists = false;

        for (int i = 0; i < adjList.getSize(); i++) {
                cout << "here";
            for (int j = 0; j < adjList[i].size(); j++) {
                if (adjList[i].get(0).getName() == departure) {

                    cout << adjList[i].get(0).getName();
                    departExists = true;
                }
                if (adjList[i].get(0).getName() == arrival) {
                    arriveExists = true;
                }
            }
        }

        if (departExists == false && arriveExists == false) {
            outFile << "Departure and arrival locations not found in list of registered cities" << endl << endl;
        }
        else if (departExists == false){
            outFile << "Departure location not found in list of registered cities" << endl << endl;
        }
        else if (arriveExists == false){
            outFile << "Arrival location not found in list of registered cities" << endl << endl;
        }
        else { //if both cities are found
            if (!(departure == arrival)) {
                int aLoc;
                //find departure linkedlist to start from
                for (int i = 0; i < adjList.getSize(); i++) {
                    if (adjList[i].get(0).getName() == departure) {
                        aLoc = i;
                    }
                }
                findPaths(adjList[aLoc].get(0), arrival); //calls functions to find paths
                outputPaths(outFile, metric); //calls function to output paths
            }
            else { //if requested flight is to the same city as the departure city
                outFile << "No paths for same-city flights can be found" << endl;
            }
        }
        inFile.getline(depart, 81, '|'); //read in next requested flight
    }
    inFile.close();
    outFile.close();
}


//use iterative backtracking to find all paths starting with airport a and ending at destination b
void FlightPlan::findPaths(AirportCity a, DSString b) {
    for (int i = 0; i < adjList.getSize(); i++) {
        adjList[i].backtrack(); //resets all iterators to first arrival node in every linkedlist
    }

    path.push(a); //add departure airport to path

    while (!path.isEmpty()) { //while searching for all possible paths has not been finished
        AirportCity temp = path.peek(); //find most recently visited Airport
        int indexLoc;
        for (int i = 0; i < adjList.getSize(); i++) { //get index of linkedlist with most recent airport as head
            if (adjList[i].get(0).getName() == temp.getName()) {
                indexLoc = i;
            }
        }

        if (adjList[indexLoc].hasNext()) { //checks to see if iterator has reached end of linkedlist (no more arrival nodes to check)
            AirportCity next = adjList[indexLoc].getNext();
            if (!path.contains(next)) { //check to see if airport is already in the path
                path.push(next); //add next airport to stack
                if (path.peek().getName() == b) { //check to see if most recent airport is destination
                    allPaths.push_back(path); //add path to vector of paths
                    path.pop(); //go back to last visited airport
                }
            }
        }
        else { //if iterator has reached end of linkedlist
            adjList[indexLoc].reset(); //put iterator back at head of departure linkedlist
            adjList[indexLoc].backtrack(); //move iterator to first arrival node
            path.pop(); //go back to last visited airport
        }
    }
}

//prints to output file possible paths up to 3 or error message if no possible paths
void FlightPlan::outputPaths(ofstream& outFile, char metric) {
    if (allPaths.empty() == true) { //if no paths were found
        outFile << "No paths could be found from requested departure city to requested arrival city." << endl << endl;
    }
    else {
        if (metric == 'C') { //if ordering by cost
            int pathNum = 0;
            double lastLowest = 0; //variable to track the most recently outputted cost
            for (int i = 0; i < 3; i++) {
                if (i > allPaths.getSize()-1) { //stops for loop iteration if less than three paths exist
                    break;
                }
                pathNum++;
                int index = -1; //variable to track index of path with lowest cost
                double lowest = 100000; //start with large number as lowest
                for (int i = 0; i < allPaths.getSize(); i++) {
                    double currentCost = 0;
                    for (int j = 0; j < allPaths[i].size(); j++) {
                        currentCost += allPaths[i].get(j).getCost(); //calculates cost of current path
                    }

                    //sets current cost as lowest if it is the next lowest after previous lowest
                    if (currentCost < lowest && currentCost > lastLowest) {
                        lowest = currentCost; //set lowest for this iteration
                        index = i; //save index of lowest
                    }
                }

                lastLowest = lowest; //sets next lowest found as next benchmark for checking lowest cost for next iteration of for loop

                double totalCost = lowest;
                int totalTime = 0;

                //outputs formatted path
                outFile << "Path " << pathNum << ": ";
                for (int i = 0; i < allPaths[index].size(); i++) { //outputs each airport in path
                    if (i == allPaths[index].size()-1) {
                        outFile << allPaths[index].get(i).getName().c_str() << ". ";
                    }
                    else {
                        outFile << allPaths[index].get(i).getName().c_str() << " -> ";
                    }
                    totalTime += allPaths[index].get(i).getTime();
                }
                outFile << "Time: " << totalTime << " "; //outputs total time
                outFile << "Cost: " << fixed << setprecision(2) << totalCost << endl; //outputs total cost
            }
        }
        else if (metric == 'T') { //if ordering by time
            int pathNum = 0;
            int lastLowest = 0; //variable to track the most recently outputted time
            for (int i = 0; i < 3; i++) {
                if (i > allPaths.getSize()-1) { //stops for loop iteration if less than three paths exist
                    break;
                }
                pathNum++;
                int index = -1; //variable to track index of path with lowest time
                int lowest = 100000; //starts with large number as lowest time
                for (int i = 0; i < allPaths.getSize(); i++) {
                    int currentTime = 0;
                    for (int j = 0; j < allPaths[i].size(); j++) {
                        currentTime += allPaths[i].get(j).getTime(); //calculates total time of current path
                    }

                    //sets current time as lowest if it is the next lowest after previous lowest
                    if (currentTime < lowest && currentTime > lastLowest) {
                        lowest = currentTime; //sets new lowest for this iteration as it is found
                        index = i; //save index of new lowest
                    }
                }

                lastLowest = lowest; //sets next lowest found as next benchmark for checking lowest time for next iteration of for loop

                int totalTime = lowest;
                double totalCost = 0;

                //outputs formatted path
                outFile << "Path " << pathNum << ": ";
                for (int i = 0; i < allPaths[index].size(); i++) {
                    if (i == allPaths[index].size()-1) {
                        outFile << allPaths[index].get(i).getName().c_str() << ". ";
                    }
                    else {
                        outFile << allPaths[index].get(i).getName().c_str() << " -> ";
                    }
                    totalCost += allPaths[index].get(i).getCost();
                }
                outFile << "Time: " << totalTime << " "; //outputs total time
                outFile << "Cost: " << fixed << setprecision(2) << totalCost << endl; //outputs total cost
            }
        }
        outFile << endl;
    }

    //remove all paths to move on to the next requested flight
    while (allPaths.empty() == false) {
        allPaths.pop_back();
    }
}


//constructor that reads in flight data and initializes adjacency list
//FlightPlan::FlightPlan(char* flightData) {

//    AdjacencyList flightList;

//    ifstream inFile;
//    inFile.open(flightData, ios::in);

//    if (!inFile) {
//        cerr << "Flight data file could not be opened" << endl;
//        exit(EXIT_FAILURE);
//    }

//    int numConnections;
//    inFile >> numConnections; //read in number of connections between different cities
//    inFile.ignore();
//    char depart[81];
//    char arrive[81];
//    double cost;
//    char airlineName[81];
//    int time;

//    inFile.getline(depart, 81, '|'); //get departure city

//    while (!inFile.eof()) {
//        inFile.getline(arrive, 81, '|'); //get arrival city
//        inFile >> cost; //get cost associated
//        inFile.ignore();
//        inFile >> time; //get time associated
//        inFile.ignore();
//        inFile >> airlineName; //get time associated
//        inFile.ignore();

//        //create String objects from char arrays
//        DSString departure(depart);
//        DSString arrival(arrive);
//        DSString airline(airlineName);

//        //add Airport data both directions
//        flightList.addAirport(departure, arrival, cost, time, airline);
//        flightList.addAirport(arrival, departure, cost, time, airline);

//        //printFlightData();

//        inFile.getline(depart, 81, '|'); //get next connection
//    }
//    inFile.close();

//}
