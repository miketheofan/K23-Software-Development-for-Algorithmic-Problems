#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>

using namespace std;

#include "./Curve.h"

class Grid{

private:

	double delta;
	vector<double> t;

public:

	Grid(double);
	~Grid();
	curve* Hashing(curve*);
};

#endif