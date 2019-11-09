#ifndef AirportCity_H
#define AirportCity_H

#include "DSString.h"
#include "DSVector.h"
#include <iostream>

class AirportCity {
    public:
        AirportCity();
        AirportCity(DSString);
        AirportCity(DSString, double, int, DSString);


        DSString getName();
        void setName(DSString);
        double getCost();
        void setCost(double);
        int getTime();
        void setTime(int);
        DSString getAirline();
        void setAirline(DSString);

        bool operator==(const AirportCity&);
        void print();

    private:
        DSString name;
        DSString airline;
        double cost;
        int time;
};

#endif // AirportCity_H
