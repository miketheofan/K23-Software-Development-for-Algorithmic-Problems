#include "../headers/items.h"

item::item(string itemID,vector<int> coordinates) : itemID(itemID){

	for(long unsigned int i=0;i<coordinates.size();i++)
		this->coordinates.push_back(coordinates[i]);
}

string item::getID(){
	return this->itemID;
}

vector<int> item::getVector(){
	return this->coordinates;
}

void item::print(){

	cout << this->itemID << " ";

	for(long unsigned int i=0;i<coordinates.size();i++)
		cout << this->coordinates[i] << " ";

	cout << endl;
}