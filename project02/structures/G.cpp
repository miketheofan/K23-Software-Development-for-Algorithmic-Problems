#include "../headers/G.h"
#include "../headers/util.h"

Gi::Gi(int k,int dimension,int w) : k(k) , w(w) {

	srand(time(NULL));

	/* The constructor first produces k random numbers in order to use them as the r. */
	for(int i=0;i<this->k;i++)
		this->rVector.push_back((int32_t)rand());

	/* The constructor also initializes k Hi (h functions) that will be used combined with r for the hashing
	of the items. */
	for(int i=0;i<this->k;i++)
		this->hVector.push_back(new Hi(dimension,w));
}

Gi::~Gi(){

	for(vector<Hi*>::iterator it = this->hVector.begin(); it != this->hVector.end(); it++)
		delete (*it);
}

/* The following function is our implementation for the g calculation. */
int32_t Gi::Hashi(item *p,int tableSize){

	long int M = pow(2,32/k);

	int result =0;

	/* First we use our k h functions. */
	for(int i=0;i<k;i++){

		/* We get the return value of each h function for given item, multiply it by the corresponding r and module the result with M. */
		int temp = module(this->hVector.at(i)->Hashi(p)*this->rVector.at(i),M);
		result += temp;
	}

	/* Then we module the result again with M using the formula given in the paper. */
	result = module(result,M);
	/* We set the trick for this certain item. */
	p->setTrick(result);
	/* Module it with table size in order to return it. */
	result = module(result,tableSize);
	
	return result;
}