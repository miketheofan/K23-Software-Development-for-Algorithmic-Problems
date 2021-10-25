#ifndef UTILLSH_H
#define UTILLSH_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>
#include <bitset>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "items.h"
#include "Hash.h"
#include "bruteFunctionsLSH.h"

double dist(int,item,item);
int32_t module(int,int);
void readDatasetLSH(string,Hash*);
vector<double>* produceNdistVector(int,int,int);
int32_t H(item*,int);
int32_t G(item*,int,int,vector<int32_t>,int);
int countItems(string);
void answerQueries(Hash,string,string,int,int);

// double mean = 0.0;
// double stddev = 1.0;

#endif