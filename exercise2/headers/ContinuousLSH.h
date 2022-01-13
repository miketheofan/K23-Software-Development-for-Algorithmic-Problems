#ifndef CONTINUOUSLSH_H
#define CONTINUOUSLSH_H

#include <iostream>
#include <vector>

using namespace std;

#include "./items.h"
#include "./Grid.h"
#include "./Hash.h"
#include "./GridContinuous.h"
#include "./frechet.hpp"
#include "./point.hpp"

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
	~Continuous();
	void insert(item*);
	vector<item*> getItems();
	item* hashCurve(item*,item*);
	item* Filtering(item*);
	item* Snapping(item*);
	item* MinMax(item*);
	item* Padding(item*);
	pair<double,item*> findNN(item*);
	pair<double,item*> findNNbrute(item*);
	vector<pair<item*,double>> rangeSearch(int,item*);

};

#endif