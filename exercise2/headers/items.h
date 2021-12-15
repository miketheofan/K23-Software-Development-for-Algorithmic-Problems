#ifndef ITEMS_H
#define ITEMS_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#include "./point.hpp"
#include "./curve.hpp"

class curve;

class item{

private:

	int trick;
	string itemID;
	vector<double> coordinates;
	int flag = -1;
	item* trueItem;
	curve* originCurve;

public:

	item(string,vector<double>);
	item(const item&);
	~item();
	void addCoordinate(double);
	string getID();
	int32_t getTrick();
	void setTrick(int32_t);
	void setTrue(item*);
	void setVector(vector<double>);
	curve* getCurve();
	void setCurve(curve*);
	vector<double> *getVector();
	int getDimension();
	double getCoordinatein(int);
	void print();
	void setFlag(int);
	int getFlag();
	const Curve& Camouflage();
};

#endif