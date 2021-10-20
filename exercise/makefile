SOURCE_FILES = ./src/
HEADER_FILES = ./headers/
DATA_FILES = ./data/
TESTS_FILES = ./tests/
LSH_FILES = ./LSH/

OBJS = $(LSH_FILES)/main.o $(SOURCE_FILES)/util.o $(DATA_FILES)/items.o
SOURCE = $(LSH_FILES)main.cpp $(SOURCE_FILES)/util.cpp $(DATA_FILES)/items.cpp
HEADER = $(HEADER_FILES)main.h $(HEADER_FILES)/util.h $(HEADER_FILES)/items.h
OUT = lsh
# ARGS = -i input.txt -q query.txt -k 1 -L 1 -o output.txt -N 1 -R 1
ARGS = -i $(TESTS_FILES)beta.txt -q $(TESTS_FILES)beta.txt -k 1 -o output.txt -N 1
CC = g++ -std=c++11
FLAGS = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) $(LSH_FILES)main.cpp

util.o: util.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)util.cpp

items.o: items.cpp
	$(CC) $(FLAGS) $(DATA_FILES)items.cpp

run:
	@mv $(OUT) ../
	@../$(OUT) $(ARGS) 	

clean:
	@rm ../$(OUT)
	@rm $(SOURCE_FILES)*.o
	@rm $(DATA_FILES)*.o
	@rm $(LSH_FILES)*.o
