SEARCH_FILES = ./search/
CLUSTER_FILES = ./cluster/
HEADER_FILES = ./headers/
TESTS_FILES = ./tests/
SOURCE_FILES = ./src/
DATA_FILES = ./data/
STRUCTURES_FILES = ./structures/
BRUTE_FILES = ./brute/
CUBE_FILES = ./CUBE/

SEARCH_OBJS = $(SEARCH_FILES)/mainSEARCH.o $(SOURCE_FILES)/util.o $(DATA_FILES)/items.o $(DATA_FILES)/Curve.o $(DATA_FILES)/Grid.o $(DATA_FILES)/GridContinuous.o $(STRUCTURES_FILES)/Hash.o $(STRUCTURES_FILES)/HashTable.o $(BRUTE_FILES)/brute.o $(STRUCTURES_FILES)/G.o $(STRUCTURES_FILES)/H.o $(STRUCTURES_FILES)/HyperCube.o $(STRUCTURES_FILES)/DiscreteLSH.o $(STRUCTURES_FILES)/ContinuousLSH.o $(SOURCE_FILES)/simplification.o $(SOURCE_FILES)/config.o $(SOURCE_FILES)/interval.o $(SOURCE_FILES)/frechet.o $(SOURCE_FILES)/curve.o $(SOURCE_FILES)/point.o  
CLUSTER_OBJS = $(CLUSTER_FILES)/mainCLUSTER.cpp
HEADERS = $(SEARCH_FILES)/mainSEARCH.h $(CLUSTER_FILES)/mainCLUSTER.h $(HEADER_FILES)/util.h $(HEADER_FILES)/Curve.H
OUT1 = outSEARCH
ARGS1 = -i $(TESTS_FILES)/dataset.csv -q $(TESTS_FILES)/query.csv -k 4 -L 1 -M 10 -probes 2 -o output.txt -algorithm Frechet -metric continuous -delta 2.5
CC = g++ -O2 -std=c++11
FLAGS = -g -c -Ο3

all: $(SEARCH_OBJS) #$(CLUSTER_OBJS)
	$(CC) -g $(SEARCH_OBJS) -o $(OUT1)
#	$(CC) -g $(CLUSTER_OBJS) -o $(OUT3)

mainSEARCH.o: mainSEARCH.cpp
	$(CC) $(FLAGS) $(SEARCH_FILES)mainSEARCH.cpp

util.o: util.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)util.cpp

items.o: items.cpp
	$(CC) $(FLAGS) $(DATA_FILES)items.cpp

Hash.o: Hash.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)Hash.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)HashTable.cpp	

brute.o: brute.cpp
	$(CC) $(FLAGS) $(BRUTE_FILES)brute.cpp

HyperCube.o: HyperCube.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)HyperCube.cpp	

DiscreteLSH.o: DiscreteLSH.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)DiscreteLSH.cpp	

ContinuousLSH.o: ContinuousLSH.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)ContinuousLSH.cpp	

Grid.o: Grid.cpp
	$(CC) $(FLAGS) $(DATA_FILES)Grid.cpp

GridContinuous.o: GridContinuous.cpp
	$(CC) $(FLAGS) $(DATA_FILES)GridContinuous.cpp

Curve.o: Curve.cpp
	$(CC) $(FLAGS) $(DATA_FILES)Curve.cpp

simplification.o: simplification.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)simplification.cpp

config.o: config.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)config.cpp

interval.o: interval.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)interval.cpp

frechet.o: frechet.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)frechet.cpp

curve.o: curve.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)curve.cpp

point.o: point.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)point.cpp

out1:
	@./$(OUT1) $(ARGS1)

debug:
	@valgrind ./$(OUT1) $(ARGS1)

clean:
	@rm $(OUT1)
	@rm $(SOURCE_FILES)*.o
	@rm $(DATA_FILES)*.o
	@rm $(SEARCH_FILES)*.o
	@rm $(STRUCTURES_FILES)*.o
# 	@rm $(CLUSTER_FILES)*.o
	@rm $(BRUTE_FILES)*.o