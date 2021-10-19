OBJS = ./src/main.o
SOURCE = ./src/main.cpp
HEADER = ./src/main.h
OUT = lsh
CC = g++ -std=c++11
FLAGS = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) ./src/main.cpp

run:
	@mv $(OUT) ../
	@../$(OUT)
