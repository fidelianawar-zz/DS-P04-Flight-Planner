#ifndef AIRPORTCITY_H
#define AIRPORTCITY_H

#include "DSString.h"
#include "DSVector.h"
#include <iostream>

class AirportCity {
    public:
        AirportCity();
        AirportCity(DSString);
        AirportCity(DSString, double, int, DSString);
        bool operator==(const AirportCity&); //overloaded equality operator
        DSString getName();
        void setName(DSString);
        double getCost();
        void setCost(double);
        int getTime();
        void setTime(int);
        DSString getAirline();
        void setAirline(DSString);

        void print(); //test function to print data contained in Airport object

    private:
        DSString name;
        double cost;
        int time;
        DSString airline;
};

#endif // AIRPORTCITY_H
