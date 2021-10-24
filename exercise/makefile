SOURCE_FILES = ./src/
HEADER_FILES = ./headers/
DATA_FILES = ./data/
TESTS_FILES = ./tests/
LSH_FILES = ./LSH/
STRUCTURES_FILES = ./structures/
BRUTE_FILES = ./brute/
CUBE_FILES = ./CUBE/

LSH_OBJS = $(LSH_FILES)/mainLSH.o $(SOURCE_FILES)/util.o $(DATA_FILES)/items.o $(LSH_FILES)/Hash.o $(STRUCTURES_FILES)/HashTable.o $(BRUTE_FILES)/bruteFunctions.o
CUBE_OBJS = $(CUBE_FILES)/mainCUBE.o
SOURCE = $(LSH_FILES)mainLSH.cpp $(SOURCE_FILES)/util.cpp $(DATA_FILES)/items.cpp $(LSH_FILES)/Hash.cpp $(STRUCTURES_FILES)/HashTable.cpp $(BRUTE_FILES)/bruteFunctions.cpp $(CUBE_FILES)/mainCUBE.cpp
HEADER = $(LSH_FILES)mainLSH.h $(HEADER_FILES)/util.h $(HEADER_FILES)/items.h $(HEADER_FILES)/HashTable.o $(HEADER_FILES)/bruteFunctions.h $(CUBE_FILES)/mainCUBE.h
OUT1 = outLSH
OUT2 = outCUBE 
ARGS1 = -i $(TESTS_FILES)dataset.txt -q $(TESTS_FILES)query.txt -k 4 -L 5 -o output.txt -N 3 -r 500
ARGS2 = -i $(TESTS_FILES)dataset.txt -q $(TESTS_FILES)query.txt -k 14 -M 10 -probes 2 -o output.txt -N 3 -r 500
CC = g++ -std=c++11
FLAGS = -g -c -Wall

all: $(LSH_OBJS) $(CUBE_OBJS)
	$(CC) -g $(LSH_OBJS) -o $(OUT1)
	$(CC) -g $(CUBE_OBJS) -o $(OUT2)

mainLSH.o: mainLSH.cpp
	$(CC) $(FLAGS) $(LSH_FILES)mainLSH.cpp

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

mainCUBE.o: mainCUBE.cpp
	$(CC) $(FLAGS) $(CUBE_FILES)mainCUBE.cpp	

lsh:
	@./$(OUT1) $(ARGS1)

cube:
	@./$(OUT2) $(ARGS2)

debug:
	@valgrind ./$(OUT) $(ARGS) -ggdb 	

clean:
	@rm $(OUT1)
	@rm $(OUT2)
	@rm $(SOURCE_FILES)*.o
	@rm $(DATA_FILES)*.o
	@rm $(LSH_FILES)*.o
	@rm $(STRUCTURES_FILES)*.o
	@rm $(CUBE_FILES)*.o