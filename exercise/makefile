SOURCE_FILES = ./src/
HEADER_FILES = ./headers/

OBJS = $(SOURCE_FILES)/main.o
SOURCE = $(SOURCE_FILES)main.cpp
HEADER = $(HEADER_FILES)main.h
OUT = lsh
CC = g++ -std=c++11
FLAGS = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)main.cpp

run:
	@mv $(OUT) ../
	@../$(OUT)	

clear:
	@rm ../$(OUT)
	@rm $(SOURCE_FILES)*.o
