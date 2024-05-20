#include "surveillance_drone.h"
#include "drone.h"
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

SurveillanceDrone::SurveillanceDrone(float startX, float startY, float endX): Drone(startX, startY, endX) {}

void SurveillanceDrone::setBatteryLevel(float batteryLevel)
{
    this->batteryLevel = batteryLevel;
}

void SurveillanceDrone::setSpeed(float speed)
{
    this->speed = speed;
}

void SurveillanceDrone::setAltitude(float altitude)
{
    this->altitude = altitude;
}

float SurveillanceDrone::getBatteryLevel() const
{
    return this->batteryLevel;
}

float SurveillanceDrone::getSpeed() const
{
    return this->speed;
}

float SurveillanceDrone::getAltitude() const
{
    return this->altitude;
}

vector<pair<int, int>> SurveillanceDrone::findShortestPath(const pair<int, int>& start, const pair<int, int>& end, const vector<vector<int>>& grid)
{
    try
    {
        vector<pair<int, int>> shortestPath;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

        map<pair<int, int>, pair<int, int>> parent;

        queue<pair<int, int>> q;
        q.push(start);
        visited[start.first][start.second] = true;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        while (!q.empty())
        {
            pair<int, int> current = q.front();
            q.pop();

            if (current == end)
            {
                while (current != start)
                {
                    shortestPath.push_back(current);
                    current = parent[current];
                }
                shortestPath.push_back(start);
                reverse(shortestPath.begin(), shortestPath.end());
                return shortestPath;
            }

            for (size_t i = 0; i < 4; ++i)
            {
                int x = current.first + dx[i];
                int y = current.second + dy[i];

                if (x >= 0 && x < static_cast<int>(grid.size()) && y >= 0 && y < static_cast<int>(grid[0].size()) && grid[x][y] == 0 && !visited[x][y])
                {
                    visited[x][y] = true;
                    parent[{x, y}] = current;
                    q.push({x, y});
                }
            }
        }

        return shortestPath;
    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return {};
    }
}
