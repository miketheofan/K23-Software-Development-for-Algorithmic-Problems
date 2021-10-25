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

pair<item*,double> HyperCube::findNN(item* queryItem){

	int minimum = numeric_limits<int>::max();
	pair<item*,double> b;
	double distance;

	int32_t hash = this->hashFunction(queryItem);
	HashNode* tempBucket;

	set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k,0);

	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		// cout << "Searching for " << (bitset<3>)*i << endl;

		tempBucket = this->cube->getBucket(*i);

		while(tempBucket != NULL){

			// cout << "Testing item: " << tempBucket->getValue()->getID() << endl;

			distance = dist(2,*queryItem,*tempBucket->getValue());
			// cout << "Distance is " << distance << endl;
			if(distance < minimum){

				b = make_pair(tempBucket->getValue(),distance);
				minimum = distance;
			}
		
			tempBucket = tempBucket->getNext();
		}
	}

	return b;
}

set<int32_t> HyperCube::HammingDist(int32_t key , int probes ,int k,int spyros){

	set<int32_t> result;
	int32_t mask;
    int masked_key;
    int thebit;
	
	if (probes == 0){

		result.insert(key);
		return result;	
	}

	for (int i=spyros ; i<k ; i++){

		mask = 1 << i;
		masked_key = key & mask;
		thebit = masked_key >> i;

		int32_t tempKey = key ^ mask;
		
		// cout << "i is " << i << " key is " << bitset<3>(key) << endl;
		// cout << "It is now " << bitset<3>(tempKey) << endl;

		set<int32_t> tempSet = HammingDist(tempKey,probes-1,k,spyros+1);
		// for(auto i = tempSet.begin();i != tempSet.end();i++){
		// bitset<3> temp = *i;
		// cout << temp << " " << endl;
		//}
		result.insert(tempKey);
		result.insert(tempSet.begin(),tempSet.end());

		spyros++;
	}

	result.insert(key);
	return result;
}


int HyperCube::coinFlip(){

	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0.01,1.99);

	return (int)distance(generator);
}