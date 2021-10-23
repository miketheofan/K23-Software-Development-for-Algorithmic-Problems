#ifndef HASH_H
#define HASH_H

#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

#include "items.h"
#include "HashTable.h"

class Hash{

private:

	int k;
	int L;
	int w;
	int size;
	vector<item*> items;
	vector<HashTable*> hashTables;

public:

	Hash(int,int,int,int);
	~Hash();
	void insert(item*);
	item* findNN(item*);
	void print();

};

#endif