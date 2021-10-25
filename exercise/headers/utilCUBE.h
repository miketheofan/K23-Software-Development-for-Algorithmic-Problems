#ifndef UTILCUBE_H
#define UTILCUBE_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

#include "HyperCube.h"
#include "bruteFunctionsCUBE.h"

void readDatasetCUBE(string,HyperCube*);
int32_t H(item *,int);
vector<double>* produceNdistVector(int,int,int);
double dist(int,item,item);
void answerQueries(HyperCube,string,string);

#endif