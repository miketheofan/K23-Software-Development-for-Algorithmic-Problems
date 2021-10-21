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

	for(int i=0;i<this->L;i++)
		this->hashTables.at(i).insert(pair<int32_t,item*>( G(newItem,this->w,this->k,this->size) , newItem ));
}