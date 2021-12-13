#ifndef GRIDCONTINUOUS_H
#define GRIDCONTINUOUS_H

#include <vector>
#include <random>

using namespace std;

#include "./items.h"

class GridContinuous{

private:

	double delta;
	double t;

public:

	GridContinuous(double);
	item* Hashing(item*);

};

#endif