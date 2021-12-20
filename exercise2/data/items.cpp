#include "../headers/items.h"

item::item(string itemID,vector<double> coordinates) : itemID(itemID){
	this->coordinates = coordinates;
	this->trueItem = NULL;
	this->originCurve = NULL;
}

item::item(const item &i){

	this->itemID = i.itemID;
	this->coordinates = i.coordinates;
}

item::~item(){}

void item::addCoordinate(double c){
	this->coordinates.push_back(c);
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

void item::setTrue(item* i){
	this->trueItem = i;
}

void item::setVector(vector<double> v){
	this->coordinates = v;
}


void item::setCurve(curve* c){
	this->originCurve = c;
}

curve* item::getCurve(){
	return this->originCurve;
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

void item::setFlag(int flag){
	this->flag = flag;
}

int item::getFlag(){
	return this->flag;
}

const Curve& item::Camouflage(){

	// cout << "Entered Camouflage for " << this->trueItem->getID() << " with size " << this->trueItem->getDimension() << endl;
	// cout << "ITEM'S is " << this->getID() << " with size " << this->getDimension() << endl;
	// this->trueItem->print();
	Curve* tempCurve = new Curve(this->getDimension(),this->getID());

	// item* tempItem;
	// if(!query)
	// 	tempItem = this->trueItem;
	// else
	// 	tempItem = this;

	item* tempItem;
	if(this->trueItem != NULL)
		tempItem = this->trueItem;
	else
		tempItem = this;

	// cout << "true item is " << tempItem->getID() << endl;

	for(int i=0;i<(double)tempItem->getVector()->size();i++){

		Point* tempPoint = new Point(tempItem->getDimension());
		tempPoint->set(i,tempItem->getVector()->at(i));

		tempCurve->push_back(*tempPoint);
	}

	return *tempCurve;

}