#include <iostream>
#include "rrt.h"

#include <vector>
using namespace std;

int main() 
{
    
    RRTClass rrt(600,600);

    vector<Point> obstaculo = {
        {200,200},
        {200,400},
        {400,400},
        {400,200},
    };
    rrt.getInput({0,0},{600,600});
    rrt.addObstacule(obstaculo);
   rrt.RRTRun();
}