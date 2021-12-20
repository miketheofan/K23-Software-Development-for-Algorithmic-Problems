#include "../headers/Curve.h"

curve::curve(string id): id(id){}

curve::curve(const curve &c){

	this->id = c.id;
	this->coordinates = c.coordinates;
}

curve::~curve(){}

void curve::addCoordinate(item* i){

	// cout << "Inserting in curve " << this->id;
	// i->print();

	this->coordinates.push_back(i);
}

void curve::setOriginal(item* i){
	this->originalItem = i;
}

item* curve::getOriginal(){
	return this->originalItem;
}

vector<item*>* curve::getCoordinates(){
	return &this->coordinates;
}

string curve::getID(){
	return this->id;
}

void curve::print(){

	int count =0;
	for(vector<item*>::iterator it = this->coordinates.begin();it != this->coordinates.end();it++){

		cout << "Item: " << count++ << " ";
		(*it)->print();
		cout << endl;
	}
}

int curve::getSize(){
	return this->coordinates.size();
}

item* curve::getCoordinateat(int index){
	return this->coordinates.at(index);
}