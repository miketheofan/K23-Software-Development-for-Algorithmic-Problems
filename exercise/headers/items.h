#ifndef ITEMS_H
#define ITEMS_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class item{

private:

	string itemID;
	vector<int> coordinates;

public:

	item(string,vector<int>);
	string getID();
	vector<int> getVector();
	void print();
};

#endif