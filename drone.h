#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <fstream>
#include <vector>
#include<iostream>
using namespace std;

class Drone
{
protected:
    float batteryLevel;
    float speed;
    float altitude;

public:
    Drone(float battery = 100.0f, float spd = 0.0f, float alt = 0.0f);
    float getBatteryLevel() const;
    float getSpeed() const;
    float getAltitude() const;
    void saveParametersToFile(const string& filename) const;
};

#endif // DRONE_H
