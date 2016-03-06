CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: p1

p1: p1.o
	$(CC) $(LFLAGS) -o p1 p1.o

p1.o: p1.cpp LinkedList.h Order.h Queue.h Stack.h Stack.cpp SuperMarket.h SuperMarket.cpp
	$(CC) $(CFLAGS) p1.cpp

clean:
	rm -rf *.o
	rm -rf
