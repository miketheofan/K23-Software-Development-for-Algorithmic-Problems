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
	string algorithm;
	vector<item*> items;
	GridContinuous* grid;
	Hash* LSH;

public:

	Continuous(int,int,int,int,int,string);
	void insert(item*);
	void Filtering();
	void Snapping();
	void MinMax();
	void Padding();
};

#endif