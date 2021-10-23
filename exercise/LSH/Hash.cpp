#include "../headers/Hash.h"
#include "../headers/util.h"

Hash::Hash(int k,int L,int w,int size) : k(k), L(L), w(w), size(size) {

	for(int i=0;i<this->L;i++){

		HashTable *tempMap = new HashTable(size);
		hashTables.push_back(tempMap);
	}
}

Hash::~Hash(){}

void Hash::insert(item* newItem){

	this->items.push_back(newItem);

	for(int i=0;i<this->L;i++){

		int temp = G(newItem,this->w,this->k,this->size);
		cout << "Hashtable " << i << " inserting " << newItem->getID() << " in " << temp << endl;
		this->hashTables.at(i)->insert(temp , newItem );
	}

	cout << endl;
}

void Hash::print(){

	for(int i=0;i<this->L;i++){

		cout << "Hash table: " << i << ": " << endl;
		// pair<unordered_map<int32_t,item *>::iterator,unordered_map<uint32_t,item*>::iterator> it = this->hashTables.at(i).equal_range();

		// for(std::pair<int32_t,item*> element: this->hashTables.at(i)){
		
		// 	// cout << element.second->getID() << " ";
		// 	cout << "Bucket: " << element.first << ": ";
		// 	for ( auto it = this->hashTables.at(i).begin(element.first); it != this->hashTables.at(i).end(element.first); ++it)
		// 		cout << it->second->getID() << " ";

		// 	cout << endl;

		// }

		this->hashTables.at(i)->print();


		cout << endl;
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