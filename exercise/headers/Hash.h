#ifndef HASH_H
#define HASH_H

#include "items.h"

using namespace std;

#include <vector>
#include <map>

class Hash{

private:

	int k;
	int L;
	int w;
	int size;
	vector<item*> items;
	vector<map<int32_t,item*>> hashTables;

public:

	Hash(int,int,int,int);
	~Hash();
	void insert(item*);

};

#endif