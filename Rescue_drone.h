#ifndef RESCUEDRONE_H
#define RESCUEDRONE_H

#include "Drone.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include<iostream>
using namespace std;

class RescueDrone : public Drone
{
private:
    pair<int, int> fireLocation;

public:
    RescueDrone(float battery = 100.0f, float spd = 0.0f, float alt = 0.0f);

    void setBatteryLevel(float batteryLevel)
    {
         this->batteryLevel = batteryLevel;
    }
    void setSpeed(float speed)
    {
         this->speed = speed;
    }
    void setAltitude(float altitude)
    {
         this->altitude = altitude;
    }

    void setFireLocation(const pair<int, int>& location);
    pair<int, int> getFireLocation() const;
    bool detectFire(const vector<vector<int>>& obstacles);
    void extinguishFire(sf::RenderWindow& window);
};

#endif // RESCUEDRONE_H
