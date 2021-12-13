#include "../headers/ContinuousLSH.h"

Continuous::Continuous(int k,int w,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm){

	this->grid = new GridContinuous(delta);
	this->LSH = new Hash(k,w,L,size,dimension*2,this->algorithm);
	this->M = 100000;
}

void Continuous::insert(item* i){


}