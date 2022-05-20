#ifndef RRT
#define RRT

#include <iostream>
#include <cstdio>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include "geometry.h"



class RRTClass
{
public:
    RRTClass(const int w, const int h) : HEIGHT(h), WIDTH(w){}
    ~RRTClass(){}

    void getInput(Point start , Point target);
    void addObstacule(std::vector<Point>&);
    void RRTRun();

private:
    const int WIDTH;
    const int HEIGHT;
    const int RADIUS =  5;

    const double GOAL_SAMPLING_PROB = (double)(0.10);
    const double INF = (double)(1e18);

    const double JUMP_SIZE = (double)((WIDTH / 100.0 * HEIGHT / 100.0) / 1.0);
    const double DISK_SIZE = (double)(JUMP_SIZE); // Ball radius around which nearby points are found


    int whichRRT = 2;
    int obstacle_cnt = 1;
    int nodeCnt = 0;
    int goalIndex = -1;
    bool pathFound = 0;

    Point start;
    Point stop;

    vector<int> parent, nearby;
    vector<double> cost, jumps;
    vector<Point> nodes;
    vector<sf::ConvexShape> polygons;
    vector<Polygon> obstacles;

    sf::CircleShape startingPoint, endingPoint;

    void draw(sf::RenderWindow &window);

    template <typename T> // Returns a random number in [low, high]
    T randomCoordinate(T low, T high);

    bool isEdgeObstacleFree(Point a, Point b);
    Point pickRandomPoint();
    void checkDestinationReached();
    void insertNodesInPath(int rootIndex, Point &q);
    void RRTUpdate();
    void prepareInput();
    void rewire();
};



#endif