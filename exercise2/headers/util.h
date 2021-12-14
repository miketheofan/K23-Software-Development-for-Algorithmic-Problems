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
#include "./DiscreteLSH.h"
#include "./ContinuousLSH.h"

void readDataset(string,HyperCube*,vector<item*>*);
void readDataset(string,Hash*,vector<item*>*);
void readDataset(string,Discrete*,vector<item*>*);
void readDataset(string,Continuous*,vector<item*>*);
vector<double>* produceNdistVector(int,int,int);
int module(int,int);
int countItems(string);
double dist(int,item,item);
double distFrechet(item*,item*);
double distFrechetBrute(Curve*,Curve*);
void answerQueries(HyperCube*,string,string,int,string);
void answerQueries(Hash*,string,string,int,string);
void answerQueries(Discrete*,string,string,int,string);
void answerQueries(Continuous*,string,string,int,string);
int getDimension(string);
void writeToFile(string,string);

#endif