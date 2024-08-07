#include "../headers/HashTable.h"

HashTable::HashTable(int tableSize) : tableSize(tableSize){

	this->table = new HashNode*[this->tableSize];
	for(int i=0;i<this->tableSize;i++)
		table[i] = NULL;
}

HashTable::~HashTable(){

	for(int i=0;i<this->tableSize;i++)
		if(this->table[i] != NULL)
			delete this->table[i];

	delete[] this->table;
}

int HashTable::HashFunction(int32_t key){
	return key % this->tableSize;
}

/* The following function inserts an item in hash table. */
void HashTable::insert(int32_t key,item* value){

	if( table[key] == NULL )/*If this position is empty , insert it in the position,othterwise find the end of the list and insert it at the end.*/
		table[key] = new HashNode(key,value);
	else	
		table[key]->insert(key,value);
}

void HashTable::print(){

	for(int i=0;i<this->tableSize;i++){

		cout << "Bucket " << i << ": ";
		if(this->table[i] != NULL)
			this->table[i]->print();
	
		cout << endl;
	}
}

/* The following function returns a bucket that corresponds to the hash key given. */
HashNode* HashTable::getBucket(int32_t key){

	for(int i=0;i<this->tableSize;i++)
		if(this->table[i] != NULL && this->table[i]->getKey() == key)
			return this->table[i];
	
	return NULL;
}

HashNode::~HashNode(){

	if(this->next != NULL)
		delete this->next;
}

HashNode::HashNode(int32_t key,item* value) : key(key){

	this->value = value;
	this->next = NULL;
}

item* HashNode::getValue(){
	return this->value;
}

int32_t HashNode::getKey(){
	return this->key;
}

HashNode* HashNode::getNext(){
	return this->next;
}

void HashNode::insert(int32_t key,item* value){

	if(this->next != NULL)
		this->next->insert(key,value);
	else
		this->next = new HashNode(key,value);
}

void HashNode::print(){

	cout << this->value->getID() << " ";
	if(this->next != NULL) this->next->print();
}