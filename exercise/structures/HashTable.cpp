#include "../headers/HashTable.h"

HashTable::HashTable(int tableSize) : tableSize(tableSize){

	this->table = new HashNode*[this->tableSize];
	for(int i=0;i<this->tableSize;i++)
		table[i] = NULL;
}

HashTable::~HashTable(){

	for(int i=0;i<this->tableSize;i++)
		if(this->table[i] != NULL)
			this->table[i]->deleteList();

	delete[] this->table;
}

int HashTable::HashFunction(int32_t key){
	return key % this->tableSize;
}

void HashTable::insert(int32_t key,item* value){

	int hash = HashFunction(key);/*Calculate in which position of Hash Table this id given must be inserted.*/

	if( table[hash] == NULL )/*If this position is empty , insert it in the position,othterwise find the end of the list and insert it at the end.*/
		table[hash] = new HashNode(key,value);
	else	
		table[hash]->insert(key,value);
}

void HashTable::print(){

	for(int i=0;i<this->tableSize;i++){

		cout << "Bucket " << i << ": ";
		if(this->table[i] != NULL)
			this->table[i]->print();
	
		cout << endl;
	}

}

HashNode* HashTable::getBucket(int32_t key){

	for(int i=0;i<this->tableSize;i++)
		if(this->table[i] != NULL && this->table[i]->getKey() == key)
			return this->table[i];
	
	return NULL;
}

void HashNode::deleteList(){

	if(this->next != NULL)
		this->next->deleteList();

	delete this;
}

HashNode::HashNode(int32_t key,item* value) : key(key){

	this->value = new item(*value);
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