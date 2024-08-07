#ifndef HASH_H
#define HASH_H

#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

#include "./items.h"
#include "./HashTable.h"
#include "./G.h"

class Hash{

private:

	int k;
	int L;
	int w;
	int size;
	int dimension;
	vector<item*> items;
	vector<HashTable*> hashTables;
	vector<Gi*> gVector;
	
public:

	Hash(int,int,int,int,int);
	~Hash();
	void insert(item*);
	vector<pair<double,item*> > findkNN(int,item*);
    vector<pair<item*,double>> findRange(int,item*);
	void print();
	vector<item*> getItems();

};

#endif
