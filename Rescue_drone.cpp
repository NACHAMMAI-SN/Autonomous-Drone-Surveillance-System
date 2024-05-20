#include "Rescue_drone.h"
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

RescueDrone::RescueDrone(float battery, float speed, float altitude): Drone(battery, speed, altitude) {}

void RescueDrone::setFireLocation(const pair<int, int>& location)
{
    fireLocation = location;
}

pair<int, int> RescueDrone::getFireLocation() const
{
    return fireLocation;
}

bool RescueDrone::detectFire(const vector<vector<int>>& obstacles)
{
    try
    {
        static bool srandCalled = false;
        if (!srandCalled)
        {
            srand(time(NULL));
            srandCalled = true;
        }

        int randNum = rand() % 100;
        return randNum < 10;
    }
    catch(const exception& e)
    {
        cerr << "Error in detectFire(): " << e.what() << endl;
        return false;
    }
}

void RescueDrone::extinguishFire(sf::RenderWindow& window)
{
    try
    {
        sf::CircleShape fireExtinguisher(30);
        fireExtinguisher.setFillColor(sf::Color::Blue);
        fireExtinguisher.setPosition(fireLocation.first * 20, fireLocation.second * 20);
        window.draw(fireExtinguisher);

        sf::CircleShape fire(10);
        fire.setFillColor(sf::Color::Red);
        fire.setPosition(fireLocation.first * 20 + 5, fireLocation.second * 20 + 5);
        window.draw(fire);

        window.display();
        sf::sleep(sf::milliseconds(1000));

        sf::sleep(sf::milliseconds(2000));
    }
    catch(const exception& e)
    {
        cerr << "Error in extinguishFire(): " << e.what() << endl;
    }
}
