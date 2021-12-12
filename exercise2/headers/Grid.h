#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>

using namespace std;

#include "./Curve.h"

class Grid{

private:

	double delta;
	vector<double> t; // ΝΑ ΣΒΗΣΤΕΙ: Shift each dimension by t.at(i)

public:

	Grid(double);
	Curve* Hashing(Curve*);
};

#endif