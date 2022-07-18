all: compile link

compile:
	g++ -Isrc/include -c main.cpp Animation.cpp

link:
	g++ main.o Animation.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system