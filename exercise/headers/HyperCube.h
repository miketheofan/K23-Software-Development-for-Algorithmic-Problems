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
	vector<item*> items;
	vector<unordered_map<int32_t,int>> fVector;
	HashTable* cube;

public:

	HyperCube(int,int,int,int);
	~HyperCube();
	void insert(item*);
	int coinFlip();
	int32_t hashFunction(item*);
	pair<item*,double> findNN(item*);
	set<int32_t> HammingDist(int32_t , int, int,int);

};

#endif