#include "../headers/Hash.h"
#include "../headers/util.h"

Hash::Hash(int k,int L,int w,int size) : k(k), L(L), w(w), size(size) {

	for(int i=0;i<this->L;i++){

		map<int32_t,item*> tempMap;
		hashTables.push_back(tempMap);
	}
}

Hash::~Hash(){}

void Hash::insert(item* newItem){

	this->items.push_back(newItem);

	for(int i=0;i<this->L;i++){

		int temp = G(newItem,this->w,this->k,this->size);
		// cout << "Hashtable " << i << " inserting " << newItem->getID() << " in " << temp << endl;
		this->hashTables.at(i).insert(pair<int32_t,item*>( temp , newItem ));
	}
}

item* Hash::findNN(item* queryItem){

	// int minimum = numeric_limits<int>::max();
	// item *b = NULL;
	// int distance;
	// int totalItems = 0;

	// int32_t hash = G(queryItem,this->w,this->k,this->size);

	// for(int i=0;i<this->L;i++)
	// 	for(auto it = this->hashTables.at(i).begin(); it != this->hashTables.at(i).end(); it++){

	// 		distance = dist(*queryItem,it);
	// 		if(distance < minimum){

	// 			b = it;
	// 			minimum = distance;
	// 		}
			
	// 		if(++totalItems > 10*this->L) return b;

	// 	}
}