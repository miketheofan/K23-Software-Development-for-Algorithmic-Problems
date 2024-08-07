#ifndef UTILCUBE_H
#define UTILCUBE_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "./HyperCube.h"
#include "./bruteFunctionsCUBE.h"

void readDatasetCUBE(string,HyperCube*,vector<item*>*);
vector<double>* produceNdistVector(int,int,int);
double dist(int,item,item);
void answerQueries(HyperCube*,string,string,int,int,int,string);
int getDimension(string);
void writeToFile(string,string);

#endif