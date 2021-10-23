#ifndef ITEMS_H
#define ITEMS_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class item{

private:

	string itemID;
	vector<double> coordinates;

public:

	item(string,vector<double>);
	item(const item&);
	string getID();
	vector<double> *getVector();
	int getDimension();
	void print();
};

#endif