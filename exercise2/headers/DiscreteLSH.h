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
	vector<curve*> items;
	vector<Grid*> grids;
	vector<Hash*> LSH;

public:

	Discrete(int,int,int,int,int,int,string);
	~Discrete();
	void insert(item*);
	vector<item*> getItems();
	item* hashCurve(item*,int,bool);
	curve* Polygonization(item*);
	curve* Snapping(curve*,int);
	// Curve* DuplicatesRemoval(curve*);
	item* Vectorization(curve*,item*);
	item* Padding(item*,curve*);
	pair<double,curve*> findNN(item*);
	pair<double,curve*> findNNbrute(item*);
	vector<pair<item*,double>> rangeSearch(int,item*);


};

#endif