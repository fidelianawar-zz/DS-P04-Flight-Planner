#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "DSLinkedList.h"
#include "DSNode.h"
#include "DSString.h"
#include "DSVector.h"
#include "FlightPlan.h"

using namespace std;

//runs test cases without cmd args
int runCatchTests(int argc, char* argv[1]){
    return Catch::Session().run(argc,argv);
}

int main(int arc, char *argv[]){
    if(arc == 1){
        return runCatchTests(arc, argv);
    }else{
        FlightPlan flight;
        //fPlan.printFlightData(); //tests accuracy of adjacency list
        flight.readFlightData(argv[1], argv[2],argv[3]);
        //flight.readRequestedFlights(argv[2], argv[3]);
    }


}

