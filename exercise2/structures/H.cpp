#include "../headers/H.h"
#include "../headers/util.h"

Hi::Hi(int dimension,int w) : w(w){

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,w);

	this->t = distance(generator);

	/* We use normal distribution in order to generate a random vector v. */
	this->v = produceNdistVector(dimension,0.0,1.0);
}

Hi::~Hi(){
	delete this->v;
}

int32_t Hi::Hashi(item *p){

	// cout << "Entered for item ";
	// p->print();
	// cout << endl;

	/* We calculate the scaler product between vectors p and (randomly generated) v. */
	double scalerProduct = inner_product(p->getVector()->begin(),p->getVector()->end(),this->v->begin(),0.0);

	return (int32_t)floor( (scalerProduct + this->t) / (double)this->w );
}