CC = g++
FLAGS = -std=c++17 -g -Wall

SOURCES = main.cpp Tree.cpp Racers.cpp

OBJS = main.o Tree.o Racers.o

DEPS = Tree.h Racers.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

race: $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)
