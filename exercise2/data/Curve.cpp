#include "../headers/Curve.h"

Curve::Curve(string id): id(id){}

void Curve::addCoordinate(item* i){

	// cout << "Inserting in curve " << this->id;
	// i->print();

	this->coordinates.push_back(i);
}

vector<item*>* Curve::getCoordinates(){
	return &this->coordinates;
}

string Curve::getID(){
	return this->id;
}

void Curve::print(){

	int count =0;
	for(vector<item*>::iterator it = this->coordinates.begin();it != this->coordinates.end();it++){

		cout << "Item: " << count++ << " ";
		(*it)->print();
		cout << endl;
	}
}

int Curve::getSize(){
	return this->coordinates.size();
}

item* Curve::getCoordinateat(int index){
	return this->coordinates.at(index);
}