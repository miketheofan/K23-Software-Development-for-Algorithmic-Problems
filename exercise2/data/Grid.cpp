#include "../headers/Grid.h"

Grid::Grid(double delta) : delta(delta){

	/* We initialize one randomly generated using uniform distrubution t, for each dimension. */
	default_random_engine generator;
  	uniform_real_distribution<double> distribution(0,this->delta);

  	this->t.push_back(distribution(generator));
  	this->t.push_back(distribution(generator));
} 

Grid::~Grid(){}

/* The following is a function that hashes a curve given, used be the snapping function. It gets every coordinate from
each dimension and uses the according formula. */
curve* Grid::Hashing(curve* c){

	curve* newCurve = new curve(c->getID());

	double previousSnapX = -1, currentSnapX;
	double previousSnapY = -1, currentSnapY;

	for(vector<item*>::iterator it = c->getCoordinates()->begin();it != c->getCoordinates()->end();it++){

		vector<double>* tempVector = (*it)->getVector();

		vector<double> newVector;

		currentSnapX = floor((tempVector->at(0)-this->t.at(0))/this->delta + 1/2)*this->delta + this->t.at(0);
		currentSnapY = floor((tempVector->at(1)-this->t.at(1))/this->delta + 1/2)*this->delta + this->t.at(1);

		if(!(previousSnapX == currentSnapX && previousSnapY == currentSnapY)){

			newVector.push_back( floor((tempVector->at(0)-this->t.at(0))/this->delta + 1/2)*this->delta + this->t.at(0));
			newVector.push_back( floor((tempVector->at(1)-this->t.at(1))/this->delta + 1/2)*this->delta + this->t.at(1));

			newCurve->addCoordinate(new item((*it)->getID(),newVector));
		}

		previousSnapX = currentSnapX;
		previousSnapY = currentSnapY;
  	}

  	return newCurve;
}