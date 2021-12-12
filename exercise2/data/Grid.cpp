#include "../headers/Grid.h"

Grid::Grid(double delta) : delta(delta){

	default_random_engine generator;
  	uniform_real_distribution<double> distribution(0,this->delta);

  	this->t.push_back(distribution(generator));
  	this->t.push_back(distribution(generator));
} 

Curve* Grid::Hashing(Curve* curve){

	// curve->print();

	Curve* newCurve = new Curve("tempItem");
	// vector<double> temp;

  	// for(int i=0;i<curve->getDimension();i++)
	for(vector<item*>::iterator it = curve->getCoordinates()->begin();it != curve->getCoordinates()->end();it++){

		// cout << "Entered for ";
		// (*it)->print();
		// cout << endl;

		vector<double>* tempVector = (*it)->getVector();

		// cout << "Got here" << endl;

		vector<double> newVector;

		// cout << tempVector->at(1) << " -> " << floor((tempVector->at(1)-this->t.at(0))/this->delta + 1/2)*this->delta + this->t.at(0) << endl;

		newVector.push_back( floor((tempVector->at(0)-this->t.at(0))/this->delta + 1/2)*this->delta + this->t.at(0));
		// cout << "Got here" << endl;
		newVector.push_back( floor((tempVector->at(1)-this->t.at(1))/this->delta + 1/2)*this->delta + this->t.at(1));
		// cout << "Got here" << endl;

		newCurve->addCoordinate(new item("tempItem",newVector));
  	}

  	return newCurve;
  	// return new item("tempItem",temp);
}