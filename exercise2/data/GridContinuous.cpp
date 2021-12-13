#include "../headers/GridContinuous.h"

GridContinuous::GridContinuous(double delta) : delta(delta){

	default_random_engine generator;
  	uniform_real_distribution<double> distribution(0,this->delta);

  	this->t = distribution(generator);
}

item* GridContinuous::Hashing(item* i){

	vector<double> tempVector;

	for(vector<double>::iterator it = i->getVector()->begin(); it != i->getVector()->end(); it++)
		tempVector.push_back(floor(((*it)+this->t)/this->delta)*this->delta);

	return new item(i->getID(),tempVector);

}