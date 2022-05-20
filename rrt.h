#include <iostream>
#include <cstdio>
#include <random>
#include <SFML/Graphics.hpp>
#include "geometry.h"

using namespace std ; 

const int WIDTH = 800 ;
const int HEIGHT = 600 ;
const int RADIUS = 5 ; 
const double GOAL_SAMPLING_PROB = 0.10;
const double INF = 1e18;

const double JUMP_SIZE = (WIDTH/100.0 * HEIGHT/100.0)/1.0;
const double DISK_SIZE = JUMP_SIZE ; // Ball radius around which nearby points are found 

int whichRRT = 3 ; 

vector < Polygon > obstacles ; 
Point start, stop ; 
int obstacle_cnt = 1 ;

vector < Point > nodes ; 
vector < int > parent, nearby ; 
vector < double > cost, jumps ; 
int nodeCnt = 0, goalIndex = -1 ; 

vector <sf::ConvexShape> polygons ;
sf::CircleShape startingPoint, endingPoint ; 
bool pathFound = 0 ;


void getInput();
void prepareInput();
void draw(sf::RenderWindow& window);

template <typename T> // Returns a random number in [low, high] 
T randomCoordinate(T low, T high);

bool isEdgeObstacleFree(Point a, Point b);
Point pickRandomPoint();
void checkDestinationReached();
void insertNodesInPath(int rootIndex, Point& q);
void rewire();
void RRT();