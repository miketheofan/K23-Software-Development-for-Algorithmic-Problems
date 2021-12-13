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
	string algorithm;
	vector<Curve*> items;
	vector<Grid*> grids;
	vector<Hash*> LSH;

public:

	Discrete(int,int,int,int,int,int,string);
	void insert(item*);
	item* hashCurve(item*,int,bool);
	Curve* Polygonization(item*);
	Curve* Snapping(Curve*,int);
	// Curve* DuplicatesRemoval(Curve*);
	item* Vectorization(Curve*,item*);
	item* Padding(item*,Curve*);
	pair<double,Curve*> findNN(item*);
	pair<double,Curve*> findNNbrute(item*);

};

#endif