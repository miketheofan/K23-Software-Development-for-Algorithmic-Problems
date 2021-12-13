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
	item* originalItem;

public:

	Curve(string);
	Curve(const Curve &);
	void addCoordinate(item*);
	string getID();
	int getSize();
	vector<item*>* getCoordinates();
	item* getCoordinateat(int);
	void print();
};

#endif