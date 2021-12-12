#ifndef CURVE_H
#define CURVE_H

#include <iostream>
#include <vector>

using namespace std;

#include "./items.h"

class Curve{

private:

	string id;
	vector<item*> coordinates;

public:

	Curve(string);
	void addCoordinate(item*);
	vector<item*>* getCoordinates();
	void print();
};

#endif