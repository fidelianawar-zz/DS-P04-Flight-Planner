#include "AirportCity.h"

//default constructor with empty name, cost, and time
AirportCity::AirportCity() {
    setName("");
    setCost(0);
    setTime(0);
}

//constructor for head (departure) nodes of linkedlists in adjacency list
AirportCity::AirportCity(DSString name) {
    setName(name);
    setCost(0);
    setTime(0);
}

//constructor for arrival nodes attached to head nodes in linkedlists
AirportCity::AirportCity(DSString name, double cost, int time, DSString airline) {
    setName(name);
    setCost(cost);
    setTime(time);
}

//overloaded equality operator to see if two Airports are equal
bool AirportCity::operator==(const AirportCity& a) {
    if (name == a.name) {
        return true;
    }
    return false;
}

//getter for Airport name
DSString AirportCity::getName() {
    return name;
}

//setter for Airport name
void AirportCity::setName(DSString n) {
    name = n;
}

//getter for Airport cost
double AirportCity::getCost() {
    return cost;
}

//setter for Airport cost
void AirportCity::setCost(double c) {
    cost = c;
}

//getter for Airport time
int AirportCity::getTime() {
    return time;
}

//setter for Airport time
void AirportCity::setTime(int t) {
    time = t;
}
//getter for Airport time
DSString AirportCity::getAirline() {
    return airline;
}

//setter for Airport time
void AirportCity::setAirline(DSString airlineName){
    airline = airlineName;
}
//prints out Airport private member data
void AirportCity::print() {
    std::cout << name<<std::endl; //<< " " << cost << " " << time << std::endl;
}
