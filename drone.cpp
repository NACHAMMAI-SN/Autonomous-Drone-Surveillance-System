#include "drone.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

Drone::Drone(float battery, float spd, float alt): batteryLevel(battery), speed(spd), altitude(alt) {}

float Drone::getBatteryLevel() const
{
    return batteryLevel;
}
float Drone::getSpeed() const
{
    return speed;
}
float Drone::getAltitude() const
{
    return altitude;
}

void Drone::saveParametersToFile(const string& filename) const
{
    try
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << "Battery Level: " << batteryLevel << "%" <<endl;
            file << "Speed: " << speed << " m/s" <<endl;
            file << "Altitude: " << altitude << " meters" <<endl;
            file.close();
        }
        else
        {
            throw runtime_error("Unable to open file: " + filename);
        }
    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}
