#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <bitset>
#include <set>

using namespace std;

#include "items.h"
#include "HashTable.h"


class HyperCube{

private:

	int k;
	int w;
	int M;
	int probes;
	int dimension;
	double t;
	vector<item*> items;
	vector<unordered_map<int32_t,int>> fVector;
	set<int32_t> nearVertices;
	vector<double> *v;
	HashTable* cube;

public:

	HyperCube(int,int,int,int,int);
	~HyperCube();
	void insert(item*);
	int coinFlip();
	int32_t hashFunction(item*);
	pair<item*,double> findNN(item*,int);
	vector<pair<double,item*>> findkNN(item*,int,int);
	vector<pair<item*,double>> findRange(int,item*,int);
	set<int32_t> HammingDist(int32_t , int, int, int);
	vector<item*> getItems();

};

#endif