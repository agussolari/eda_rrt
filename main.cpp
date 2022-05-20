#include <iostream>
#include "rrt.h"

int main() 
{
    
    RRTClass rrt(600,600);

    rrt.getInput({0,0},{600,600});
    rrt.RRTRun();
}