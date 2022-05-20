main: geometry.o main.o rrt.o
	g++ main.o rrt.o geometry.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp rrt.cpp rrt.h geometry.cpp geometry.h
	g++ -c main.cpp

rrt.o: rrt.cpp rrt.h geometry.cpp geometry.h
	g++ -c rrt.cpp

geometry.o: geometry.cpp geometry.h
	g++ -c geometry.cpp

run:
	rm *.o
	./main
