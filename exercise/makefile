SOURCE_FILES = ./src/
HEADER_FILES = ./headers/
DATA_FILES = ./data/
TESTS_FILES = ./tests/
LSH_FILES = ./LSH/
STRUCTURES_FILES = ./structures/
BRUTE_FILES = ./brute/

OBJS = $(LSH_FILES)/main.o $(SOURCE_FILES)/util.o $(DATA_FILES)/items.o $(LSH_FILES)/Hash.o $(STRUCTURES_FILES)/HashTable.o $(BRUTE_FILES)/bruteFunctions.o
SOURCE = $(LSH_FILES)main.cpp $(SOURCE_FILES)/util.cpp $(DATA_FILES)/items.cpp $(LSH_FILES)/Hash.cpp $(STRUCTURES_FILES)/HashTable.cpp $(BRUTE_FILES)/bruteFunctions.cpp
HEADER = $(HEADER_FILES)main.h $(HEADER_FILES)/util.h $(HEADER_FILES)/items.h $(HEADER_FILES)/HashTable.o $(HEADER_FILES)/bruteFunctions.h
OUT = outLSH
ARGS = -i $(TESTS_FILES)dataset.txt -q $(TESTS_FILES)query.txt -k 4 -L 5 -o output.txt -N 1 -r 10000
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

Hash.o: Hash.cpp
	$(CC) $(FLAGS) $(LSH_FILES)Hash.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)HashTable.cpp	

bruteFunctions.o: bruteFunctions.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)bruteFunctions.cpp	

run:
# 	@mv $(OUT) ../
	@./$(OUT) $(ARGS)

debug:
	@valgrind ./$(OUT) $(ARGS) -ggdb 	

clean:
	@rm $(OUT)
	@rm $(SOURCE_FILES)*.o
	@rm $(DATA_FILES)*.o
	@rm $(LSH_FILES)*.o
	@rm $(STRUCTURES_FILES)*.o
