#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "./HyperCube.h"
#include "./Hash.h"
#include "./brute.h"

void readDatasetCUBE(string,HyperCube*,vector<item*>*);
void readDatasetLSH(string,Hash*,vector<item*>*);
vector<double>* produceNdistVector(int,int,int);
int module(int,int);
int countItems(string);
double dist(int,item,item);
void answerQueries(HyperCube*,string,string,int,int,int,string);
int getDimension(string);
void writeToFile(string,string);

#endif