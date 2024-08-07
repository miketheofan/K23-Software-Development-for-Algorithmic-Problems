#ifndef BRUTEFUNCTIONSCUBE_H
#define BRUTEFUNCTIONSCUBE_H

#include <iostream>
#include <algorithm>

using namespace std;

#include "utilCUBE.h"
#include "items.h"

double bruteNN(item*,string);
vector<pair<double,item*>> brutekNN(int,item*,string);

#endif