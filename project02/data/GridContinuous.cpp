#include "../headers/GridContinuous.h"

GridContinuous::GridContinuous(double delta) : delta(delta){

	/* We initialize one randomly generated using uniform distrubution t. */
	default_random_engine generator;
  	uniform_real_distribution<double> distribution(0,this->delta);

  	this->t = distribution(generator);
}

/* The following is a function that hashes a curve given, used be the snapping function. It gets every coordinate 
and uses the according formula. */
item* GridContinuous::Hashing(item* i){

	vector<double> tempVector;

	for(vector<double>::iterator it = i->getVector()->begin(); it != i->getVector()->end(); it++)
		tempVector.push_back(floor(((*it)+this->t)/this->delta)*this->delta);

	return new item(i->getID(),tempVector);

}