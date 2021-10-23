#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>

using namespace std;

#include "items.h"

class HashNode{

private:

	item* value;
	int32_t key;
	HashNode *next;

public:

	HashNode(int32_t,item*);
	item* getValue();
	int32_t getKey();
	HashNode* getNext();
	void insert(int32_t,item*);
	void deleteList();
	void print();

};

class HashTable{

private:

	int tableSize;
	HashNode ** table;

public:

	HashTable(int);
	~HashTable();
	void insert(int32_t,item*);
	int HashFunction(int32_t);
	void print();
	HashNode* getBucket(int32_t);
};

#endif