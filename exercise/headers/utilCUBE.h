#ifndef UTILCUBE_H
#define UTILCUBE_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

#include "HyperCube.h"

void readDatasetCUBE(string,HyperCube*);
int32_t H(item *,int);
vector<double>* produceNdistVector(int,int,int);

#endif