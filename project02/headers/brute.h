#ifndef BRUTEFUNCTIONSLSH_H
#define BRUTEFUNCTIONSLSH_H

#include <iostream>

using namespace std;

#include "util.h"
#include "items.h"

double bruteNN(item*,string);
vector<pair<double,item*>> brutekNN(int,item*,string);

#endif
