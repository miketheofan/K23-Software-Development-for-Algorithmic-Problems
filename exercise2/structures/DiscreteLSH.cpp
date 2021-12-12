#include "../headers/DiscreteLSH.h"

Discrete::Discrete(int k,int w,int L,int size,int dimension,int delta) : dimension(dimension), delta(delta), L(L){

	// this->LSH = new Hash(k,w,L,size,dimension*2);

	for(int i=0;i<L;i++){

		this->grids.push_back(new Grid(delta));
		this->LSH.push_back(new Hash(k,w,L,size,dimension*2));
	}

	this->M = 100000;
}

void Discrete::insert(item* i){

	// this->items.push_back(i);
	
	Curve* newCurve;
	item* newItem;
	
	for(int y=0;y<this->L;y++){

		newCurve = this->Polygonization(i);
		// newCurve->print();
		newCurve = this->Snapping(newCurve,y);
		// cout << "Got here" << endl;
		newItem = this->Vectorization(newCurve,i);
		this->Padding(newItem);

		this->LSH.at(y)->insert(newItem);
		// cout << "Inserted " << newItem->getID() << " in Hash table " << y << endl;
	}
}

Curve* Discrete::Snapping(Curve* curve,int index){
  	return this->grids.at(index)->Hashing(curve);
}

Curve* Discrete::Polygonization(item* i){

	int counter =0;
	vector<double> temp;

	for(vector<double>::iterator it = i->getVector()->begin();it != i->getVector()->end();it++){

		temp.push_back(++counter);
		// cout << "Inserted " << counter << " in curve " << i->getID() << endl;
		temp.push_back(*it);
		// cout << "Inserted " << (*it) << " in curve " << i->getID() << endl;
	}
	
	Curve* tempCurve = new Curve("tempCurve");
	tempCurve->addCoordinate(new item("tempItem",temp));
	
	return tempCurve;
}

item* Discrete::Vectorization(Curve* i,item* original){

	item* newItem;
	vector<double> temp;

	for(vector<item*>::iterator it = i->getCoordinates()->begin();it != i->getCoordinates()->end(); it++){

		temp.push_back((*it)->getCoordinatein(0));
		temp.push_back((*it)->getCoordinatein(1));
	}

	return new item(original->getID(),temp);
}

void Discrete::Padding(item* i){

	if(i->getVector()->size() == (unsigned long int)this->dimension*2)
		return;

	int diff = this->dimension*2 - i->getVector()->size();

	for(int y=0;y<diff;y++)
		i->addCoordinate(this->M);
}