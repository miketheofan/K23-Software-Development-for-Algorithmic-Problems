#include "../headers/Curve.h"

Curve::Curve(string id): id(id){}

void Curve::addCoordinate(item* i){
	this->coordinates.push_back(i);
}

vector<item*>* Curve::getCoordinates(){
	return &this->coordinates;
}

void Curve::print(){

	int count =0;
	for(vector<item*>::iterator it = this->coordinates.begin();it != this->coordinates.end();it++){

		cout << "Item: " << count++ << " ";
		(*it)->print();
		cout << endl;
	}
}