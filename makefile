CC = g++

all: Exe

Exe: main.o histogram.o
	$(CC) main.o histogram.o -o main.exe

main.o: main.cpp
	$(CC) -c main.cpp

histogram.o: histogram.cpp
	$(CC) -c histogram.cpp