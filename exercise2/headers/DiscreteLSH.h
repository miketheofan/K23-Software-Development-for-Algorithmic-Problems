#ifndef DISCRETELSH_H
#define DISCRETELSH_H

#include <vector>
#include <random>

using namespace std;

#include "./items.h"
#include "./Hash.h"
#include "./Grid.h"
#include "./Curve.h"

class Discrete{

private:

	int dimension;
	int delta;
	int L;
	long double M;
	vector<Curve*> items;
	vector<Grid*> grids;
	// vector<vector<pair<int,double>>> polygCurves;
	vector<Hash*> LSH;

public:

	Discrete(int,int,int,int,int,int);
	void insert(item*);
	Curve* Polygonization(item*);
	Curve* Snapping(Curve*,int);
	void DuplicatesRemoval();
	item* Vectorization(Curve*,item*);
	void Padding(item*);

};

#endif