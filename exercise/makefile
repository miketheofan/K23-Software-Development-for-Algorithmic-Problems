SOURCE_FILES = ./src/
HEADER_FILES = ./headers/
DATA_FILES = ./data/

OBJS = $(SOURCE_FILES)/main.o $(SOURCE_FILES)/util.o $(DATA_FILES)/items.o
SOURCE = $(SOURCE_FILES)main.cpp $(SOURCE_FILES)/util.cpp $(DATA_FILES)/items.cpp
HEADER = $(HEADER_FILES)main.h $(HEADER_FILES)/util.h $(HEADER_FILES)/items.h
OUT = lsh
# ARGS = -i input.txt -q query.txt -k 1 -L 1 -o output.txt -N 1 -R 1
ARGS = -i input.txt -q query.txt -k 1 -o output.txt -N 1
CC = g++ -std=c++11
FLAGS = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)main.cpp

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
