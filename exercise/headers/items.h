#ifndef ITEMS_H
#define ITEMS_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class item{

private:

	int dimension =0;
	string itemID;
	vector<int> coordinates;

public:

	item(string,vector<int>);
	int getDimension();
	string getID();
	vector<int> getVector();
	void print();
};

#endif