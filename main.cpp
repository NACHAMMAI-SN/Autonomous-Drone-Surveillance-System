#include "Drone.h"
#include "Surveillance_drone.h"
#include "Rescue_drone.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdexcept>
using namespace std;

void savePointToFile(const string& filename, const pair<int, int>& point)
{
    try {
        ofstream file(filename);
        if (file.is_open())
        {
            file << point.first << " " << point.second;
            file.close();
        }
        else
        {
            throw runtime_error("Unable to save point to file: " + filename);
        }
    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

pair<int, int> loadPointFromFile(const string& filename)
{
    pair<int, int> point;
    try
    {
        ifstream file(filename);
        if (file.is_open())
        {
            file >> point.first >> point.second;
            file.close();
        }
        else
        {
            throw runtime_error("Unable to load point from file: " + filename);
        }
    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return point;
}

vector<vector<int>> generateRandomObstacles(const pair<int, int>& source, const pair<int, int>& destination, int width, int height)
{
    vector<vector<int>> obstacles(height, vector<int>(width, 0));
    srand(time(NULL));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == source.second && j == source.first) || (i == destination.second && j == destination.first))
                continue;

            if (rand() % 5 == 0)
                obstacles[i][j] = 1;
        }
    }

    return obstacles;
}

void drawObstacles(sf::RenderWindow& window, const vector<vector<int>>& obstacles)
{
    sf::RectangleShape obstacle(sf::Vector2f(20, 20));
    for (size_t i = 0; i < obstacles.size(); ++i)
    {
        for (size_t j = 0; j < obstacles[0].size(); ++j)
        {
            if (obstacles[i][j] == 1)
            {
                obstacle.setPosition(j * 20, i * 20);
                obstacle.setFillColor(sf::Color::Black);
                window.draw(obstacle);
            }
        }
    }
}

void drawTrajectory(sf::RenderWindow& window, const vector<pair<int, int>>& trajectory, const pair<int, int>& source, const pair<int, int>& destination, const sf::Font& font)
{
    sf::CircleShape point(3);
    point.setFillColor(sf::Color::Red);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);

    point.setPosition(source.first * 20, source.second * 20);
    window.draw(point);
    text.setString("A");
    text.setPosition(source.first * 20 - 10, source.second * 20 - 25);
    window.draw(text);

    point.setPosition(destination.first * 20, destination.second * 20);
    window.draw(point);
    text.setString("B");
    text.setPosition(destination.first * 20 - 10, destination.second * 20 - 25);
    window.draw(text);

    for (const auto& p : trajectory)
    {
        point.setPosition(p.first * 20, p.second * 20);
        window.draw(point);
    }
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cerr << "Error: Unable to load font file" <<endl;
        return -1;
    }

    pair<int, int> source, destination;
    cout << "Enter source point (x y): ";
    cin >> source.first >> source.second;
    cout << "Enter destination point (x y): ";
    cin >> destination.first >> destination.second;

    savePointToFile("source.txt", source);
    savePointToFile("destination.txt", destination);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Trajectory Analysis");

    source = loadPointFromFile("source.txt");
    destination = loadPointFromFile("destination.txt");

    int width = 40;
    int height = 30;
    vector<vector<int>> obstacles = generateRandomObstacles(source, destination, width, height);

    SurveillanceDrone surveillanceDrone(source.first, source.second, destination.first);
    surveillanceDrone.setBatteryLevel(80.0f);
    surveillanceDrone.setSpeed(10.0f);
    surveillanceDrone.setAltitude(50.0f);

    RescueDrone rescueDrone(source.first, source.second, destination.first);
    rescueDrone.setBatteryLevel(90.0f);
    rescueDrone.setSpeed(8.0f);
    rescueDrone.setAltitude(60.0f);

    vector<pair<int, int>> initialTrajectorySurveillance = surveillanceDrone.findShortestPath(source, destination, obstacles);
    vector<pair<int, int>> initialTrajectoryRescue = initialTrajectorySurveillance;

    vector<vector<int>> noObstacles = obstacles;
    for (auto& row : noObstacles)
    {
        for (auto& cell : row)
        {
            cell = 0;
        }
    }

    vector<pair<int, int>> shortestPathTrajectorySurveillance = surveillanceDrone.findShortestPath(source, destination, noObstacles);
    vector<pair<int, int>> shortestPathTrajectoryRescue = shortestPathTrajectorySurveillance;

    float initialBatteryLevelSurveillance = surveillanceDrone.getBatteryLevel();
    float initialSpeedSurveillance = surveillanceDrone.getSpeed();
    float initialAltitudeSurveillance = surveillanceDrone.getAltitude();

    float initialBatteryLevelRescue = rescueDrone.getBatteryLevel();
    float initialSpeedRescue = rescueDrone.getSpeed();
    float initialAltitudeRescue = rescueDrone.getAltitude();

    pair<int, int> fireLocation;
    bool fireDetected = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        drawObstacles(window, obstacles);

        drawTrajectory(window, initialTrajectorySurveillance, source, destination, font);
        drawTrajectory(window, shortestPathTrajectorySurveillance, source, destination, font);

        drawTrajectory(window, initialTrajectoryRescue, source, destination, font);
        drawTrajectory(window, shortestPathTrajectoryRescue, source, destination, font);

        if (!fireDetected)
        {
            fireDetected = rescueDrone.detectFire(obstacles);
            if (fireDetected)
            {
                fireLocation.first = rand() % width;
                fireLocation.second = rand() % height;
                rescueDrone.setFireLocation(fireLocation);
                cout << "Fire detected at location: " << fireLocation.first << ", " << fireLocation.second <<endl;
            }
        }
        else
        {
            rescueDrone.extinguishFire(window);
            fireDetected = false;
        }

        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    cout << "\n--------------------------------------------------------------------------"<<endl;
    cout << "\n\t\t\tSurveillance Drone Information:" <<endl;
    cout << "Initial Battery Level\t: " << initialBatteryLevelSurveillance << "%" <<endl;
    cout << "Initial Speed\t\t: " << initialSpeedSurveillance << " m/s" <<endl;
    cout << "Initial Altitude\t: " << initialAltitudeSurveillance << " meters" <<endl;
    cout << "Current Battery Level\t: " << surveillanceDrone.getBatteryLevel() << "%" <<endl;
    cout << "Current Speed\t\t: " << surveillanceDrone.getSpeed() << " m/s" <<endl;
    cout << "Current Altitude\t: " << surveillanceDrone.getAltitude() << " meters" <<endl;
    cout << "\n--------------------------------------------------------------------------"<<endl;
    cout << "\n\t\t\tRescue Drone Information:" <<endl;
    cout << "Initial Battery Level\t: " << initialBatteryLevelRescue << "%" << endl;
    cout << "Initial Speed\t\t: " << initialSpeedRescue << " m/s" <<endl;
    cout << "Initial Altitude\t: " << initialAltitudeRescue << " meters" <<endl;
    cout << "Current Battery Level\t: " << rescueDrone.getBatteryLevel() << "%" <<endl;
    cout << "Current Speed\t\t: " << rescueDrone.getSpeed() << " m/s" <<endl;
    cout << "Current Altitude\t: " << rescueDrone.getAltitude() << " meters" << endl;

    return 0;
}
