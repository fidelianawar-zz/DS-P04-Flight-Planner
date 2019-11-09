#include "AirportCity.h"

//default constructor
AirportCity::AirportCity() {
    name = "";
    airline = "";
    cost = 0;
    time = 0;
}

//constructor for head (departure) nodes LL
AirportCity::AirportCity(DSString cityName) {
    this->name = cityName;
    this->airline = "";
    this->cost = 0;
    this->time = 0;

}

//constructor for arrival nodes
AirportCity::AirportCity(DSString name, double cost, int time, DSString airline) {
    this-> name = name;
    this-> cost = cost;
    this-> time = time;
    this-> airline = airline;

}

//checks if two AirportCities are equal or not
bool AirportCity::operator==(const AirportCity& a) {
    if (name == a.name) {
        return true;
    }
    return false;
}

DSString AirportCity::getName() {
    return name;
}

void AirportCity::setName(DSString n) {
    name = n;
}

double AirportCity::getCost() {
    return cost;
}

void AirportCity::setCost(double c) {
    cost = c;
}

int AirportCity::getTime() {
    return time;
}

void AirportCity::setTime(int t) {
    time = t;
}

DSString AirportCity::getAirline(){
    return airline;
}

void AirportCity::setAirline(DSString airlineName){
    airline = airlineName;
}

void AirportCity::print() {
    std::cout << name << " " << cost << " " << time << " " << airline << std::endl;
}

