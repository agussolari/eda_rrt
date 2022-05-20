#include <iostream>
#include "rrt.h"

int main() {
	getInput(); prepareInput(); 
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Basic Anytime RRT");

	nodeCnt = 1; nodes.push_back(start); int iterations = 0 ; 
	parent.push_back(0); cost.push_back(0);
    sf::Time delayTime = sf::milliseconds(5);

    cout << endl << "Starting node is in Pink and Destination node is in Blue" << endl << endl ; 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
            	window.close();
            	return 0; exit(0);
            }
        }
        RRT(); iterations++;
        
		if(iterations % 500 == 0) {
			cout << "Iterations: " << iterations << endl ; 
			if(!pathFound) cout << "Not reached yet :( " << endl ;
			else cout << "Shortest distance till now: " << cost[goalIndex] << " units." << endl ;
			cout << endl ;
		}

		//sf::sleep(delayTime);
		window.clear();
		draw(window); 
        window.display();
    }
}