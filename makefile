main:
	g++ -std=c++11 -c geometry.h rrt.cpp 
	g++ rrt.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app 