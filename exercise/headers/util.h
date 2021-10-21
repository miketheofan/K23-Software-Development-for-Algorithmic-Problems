#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>

#include "items.h"

double dist(item,item);
int module(int,int);
void readDataset(string);
vector<double>* produceNdistVector(int,int,int);
int32_t H(item,int,int);
int32_t G(item,int,int,int);

// double mean = 0.0;
// double stddev = 1.0;

#endif