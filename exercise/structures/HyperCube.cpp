#include "../headers/HyperCube.h"
#include "../headers/utilCUBE.h"

HyperCube::HyperCube(int k,int w,int M,int probes) : k(k), w(w), M(M), probes(probes){

	this->cube = new HashTable(pow(2,this->k));

	for(int i=0;i<this->k;i++){

		unordered_map<int32_t,int> temp;
		this->fVector.push_back(temp);
	}
}

HyperCube::~HyperCube(){}

void HyperCube::insert(item *it){

	this->items.push_back(it);
	this->cube->insert(this->hashFunction(it),it);

}

int32_t HyperCube::hashFunction(item* it){

	int32_t key = 0;

	for(int i=0;i<this->k;i++){

		int32_t hash = H(it,this->w);


		if(fVector.at(i).find(hash) == fVector.at(i).end())
			fVector.at(i)[hash] = coinFlip();

		key = key << 1;
		key = key | fVector.at(i)[hash];
	}

	return key;
}

int HyperCube::coinFlip(){

	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,1);

	return (int)distance(generator);
}