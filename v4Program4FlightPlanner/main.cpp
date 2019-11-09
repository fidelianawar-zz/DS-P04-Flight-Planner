#define CATCH_CONFIG_RUNNER

#include "DSLinkedList.h"
#include "DSString.h"
#include "DSVector.h"
#include "AirportCity.h"
#include "FlightPlan.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int runCatchTests(int argc, char* const argv[]) {
    return Catch::Session().run(argc, argv);
}
int main(int argc, char* const argv[]) {

    if(argc == 1){
        return runCatchTests(argc, argv);
    }else{
        FlightPlan flight;
        flight.readInputData(argv[1]);
        flight.readRequestedFlights(argv[2],argv[3]);
    }

}
