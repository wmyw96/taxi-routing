all: main
main: graph.o graph.h main.o
	g++ graph.o main.o -o main
graph.o: graph.h graph.cpp
	g++ -c graph.cpp -o graph.o
main.o: main.cpp
	g++ -c main.cpp -o main.o
