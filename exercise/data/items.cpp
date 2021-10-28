#include "../headers/items.h"

item::item(string itemID,vector<double> coordinates) : itemID(itemID){

	// for(long unsigned int i=0;i<coordinates.size();i++)
	// 	this->coordinates.push_back(coordinates[i]);

	this->coordinates = coordinates;
}

item::item(const item &i){

	this->itemID = i.itemID;
	this->coordinates = i.coordinates;
}

string item::getID(){
	return this->itemID;
}

int32_t item::getTrick(){
	return this->trick;
}

void item::setTrick(int32_t trick){
	this->trick = trick;
}

vector<double> *item::getVector(){
	return &this->coordinates;
}

int item::getDimension(){
	return this->coordinates.size();
}

double item::getCoordinatein(int index){

	for(int i=0; i<this->getDimension(); i++)
		if(i == index)
			return this->coordinates.at(i);

	return -1;
}

void item::print(){

	cout << this->itemID << " ";

	for(long unsigned int i=0;i<coordinates.size();i++)
		cout << this->coordinates[i] << " ";

	cout << endl;
}