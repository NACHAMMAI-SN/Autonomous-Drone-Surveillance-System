#ifndef SURVEILLANCE_DRONE_H
#define SURVEILLANCE_DRONE_H

#include "drone.h"

#include <vector>
#include <utility>
#include<iostream>
using namespace std;

class SurveillanceDrone : public Drone
{
public:
    SurveillanceDrone(float initialBattery, float initialSpeed, float initialAltitude);
    void setBatteryLevel(float level);
    float getBatteryLevel() const;
    void setSpeed(float speed);
    float getSpeed() const;
    void setAltitude(float altitude);
    float getAltitude() const;
    vector<pair<int, int>> findShortestPath(const pair<int, int>& start, const pair<int, int>& end, const vector<vector<int>>& grid);
private:
    float batteryLevel;
    float speed;
    float altitude;
};

#endif
