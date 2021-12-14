#ifndef CONTINUOUSLSH_H
#define CONTINUOUSLSH_H

#include <iostream>
#include <vector>

using namespace std;

#include "./items.h"
#include "./Grid.h"
#include "./Hash.h"
#include "./GridContinuous.h"

class Continuous{

private:

	int dimension;
	int delta;
	int L;
	long double M;
	double epsilon;
	string algorithm;
	vector<item*> items;
	GridContinuous* grid;
	Hash* LSH;

public:

	Continuous(int,int,int,int,int,int,string);
	void insert(item*);
	item* hashCurve(item*);
	item* Filtering(item*);
	item* Snapping(item*);
	item* MinMax(item*);
	item* Padding(item*);
	pair<double,item*> findNN(item*);
};

#endif