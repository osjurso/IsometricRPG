#ifndef ISORPG_PATHFINDING_H
#define ISORPG_PATHFINDING_H

// Astar.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>


const int dir = 8; // number of possible directions to go at any position
static int dx[dir] = {1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir] = {0, 1, 1, 1, 0, -1, -1, -1};

class node {
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

public:
    node(int xPos, int yPos, int level, int priority) : xPos(xPos), yPos(yPos), level(level), priority(priority) {};

    int getxPos() const { return xPos; }
    int getyPos() const { return yPos; }
    int getLevel() const { return level; }
    int getPriority() const { return priority; }

    void updatePriority(const int &xDest, const int &yDest) {
        priority = level + estimate(xDest, yDest) * 10; //A*
    }

    // give better priority to going strait instead of diagonally
    void nextLevel(const int &i) // i: direction
    {
        level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
    }

    // Estimation function for the remaining distance to the goal.
    const int &estimate(const int &xDest, const int &yDest) const
    {
        static int xd, yd, d;
        xd = xDest - xPos;
        yd = yDest - yPos;

        // TODO: Test om dette påvirker performance, sqrt er en tung operasjon.

        // Euclidian Distance
        d = static_cast<int>(sqrt(xd * xd + yd * yd));

        // Manhattan distance
        //d=abs(xd)+abs(yd);

        // Chebyshev distance
        //d=max(abs(xd), abs(yd));

        return (d);
    }

    void loadMapData(int width, int height);

};

// Determine priority (in the priority queue)
bool operator<(const node &a, const node &b);

// A-star algorithm.
// The route returned is a string of direction digits.
std::string pathFind(const int &xStart, const int &yStart, const int &xFinish, const int &yFinish);

#endif //ISORPG_PATHFINDING_H
