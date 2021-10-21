#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

#include "items.h"

double dist(item,item);
void readDataset(string);
vector<double>* produceNdistVector(int,int,int);
int32_t H(item,int);

// double mean = 0.0;
// double stddev = 1.0;

#endif