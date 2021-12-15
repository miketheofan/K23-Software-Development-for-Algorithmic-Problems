#ifndef CURVE_H
#define CURVE_H

#include <iostream>
#include <vector>

using namespace std;

#include "./items.h"

class curve{

private:

	string id;
	vector<item*> coordinates;
	item* originalItem;

public:

	curve(string);
	curve(const curve &);
	void addCoordinate(item*);
	string getID();
	int getSize();
	vector<item*>* getCoordinates();
	item* getCoordinateat(int);
	void print();
};

#endif