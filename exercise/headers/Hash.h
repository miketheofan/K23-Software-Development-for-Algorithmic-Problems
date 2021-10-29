#ifndef HASH_H
#define HASH_H

#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

#include "items.h"
#include "HashTable.h"

class Hash{

private:

	int k;
	int L;
	int w;
	vector<int32_t> rVector;
	int size;
	int dimension;
	double t;
	vector<item*> items;
	vector<HashTable*> hashTables;
	vector<double> *v;
	
public:

	Hash(int,int,int,int,int);
	~Hash();
	void insert(item*);
	pair<item*,double> findNN(item*);
	vector<pair<double,item*> > findkNN(int,item*);
    vector<pair<item*,double>> findRange(int,item*);
	void print();
	vector<item*> getItems();

};

#endif
