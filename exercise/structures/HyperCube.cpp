#include "../headers/HyperCube.h"
#include "../headers/utilCUBE.h"

HyperCube::HyperCube(int k,int w,int M,int probes,int dimension) : k(k), w(w), M(M), probes(probes), dimension(dimension) {

	this->cube = new HashTable(pow(2,this->k));

	for(int i=0;i<this->k;i++){

		unordered_map<int32_t,int> temp;
		this->fVector.push_back(temp);
	}

	this->v = produceNdistVector(this->dimension,0.0,1.0);

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,this->w);

	this->t = distance(generator);
}

HyperCube::~HyperCube(){

	delete this->v;
	delete this->cube;
}

void HyperCube::insert(item *it){

	this->items.push_back(it);

	this->cube->insert(this->hashFunction(it),it);
}

int32_t HyperCube::hashFunction(item* it){

	int32_t key = 0;

	for(int i=0;i<this->k;i++){

		int32_t hash = H(it,this->w,this->v,this->t);

		// cout << "hash returned " << hash << endl;

		if(fVector.at(i).find(hash) == fVector.at(i).end())
			fVector.at(i)[hash] = coinFlip();


		key = key << 1;
		key = key | fVector.at(i)[hash];
	}
	
	return key;
}

pair<item*,double> HyperCube::findNN(item* queryItem,int M){

	double minimum = numeric_limits<int>::max();
	pair<item*,double> b;
	double distance;

	int flag =0;

	int32_t hash = this->hashFunction(queryItem);
	// cout << "hash returned: " << (bitset<14>)hash << endl;
	HashNode* tempBucket;

	set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k);

	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		// cout << "Searching for " << (bitset<3>)*i << endl;

		tempBucket = this->cube->getBucket(*i);

		while(tempBucket != NULL){

			// cout << "Testing item: " << tempBucket->getValue()->getID() << endl;

			distance = dist(2,*queryItem,*tempBucket->getValue());
			// cout << "Distance is " << distance << endl;
			// cout << "minimum is " << minimum << endl;
			if(isgreater(minimum,distance)){

				// cout << "new minimum is: " << tempBucket->getValue()->getID() << " with distance: " << distance << endl;
				b = make_pair(tempBucket->getValue(),distance);
				minimum = distance;
			}
		
			tempBucket = tempBucket->getNext();
		
			if(++flag == M) return b;
		}
	}

	return b;
}

vector<pair<double,item*>> HyperCube::findkNN(item* queryItem,int M,int k){

	double minimum = numeric_limits<int>::max();

	vector<pair<double,item*>> results;

	int32_t hash = this->hashFunction(queryItem);

	int flag =0;

	HashNode* tempBucket;

	set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k);

	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		tempBucket = this->cube->getBucket(*i);
		while(tempBucket != NULL){

			flag++;

			double distance = dist(2,*queryItem,*tempBucket->getValue());
			if(isgreater(minimum,distance)){

				// cout << "Entered for " << tempBucket->getValue()->getID() << " with distance " << distance << endl;

				if((int)results.size() == k){

					results.pop_back();
					results.push_back(make_pair(distance,tempBucket->getValue()));

					sort(results.begin(),results.end());
					
					minimum	= results.at(results.size()-1).first;

				}else{

					results.push_back(make_pair(distance,tempBucket->getValue()));
					sort(results.begin(),results.end());
				}
			}

			tempBucket = tempBucket->getNext();

			if(++flag == M) return results;

		}
	}

	return results;
}

vector<pair<item*,double>> HyperCube::findRange(int r,item* queryItem,int M){

	vector<pair<item*,double>> queries;

	int32_t hash = this->hashFunction(queryItem);
    HashNode* tempBucket;

    int flag = 0;

    double distance;

    set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k);

	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		tempBucket = this->cube->getBucket(*i);
		while(tempBucket != NULL){
                              	
	      	distance = dist(2,*queryItem,*tempBucket->getValue());
	        
	        if(isgreater(r,distance))
	            queries.push_back(make_pair(tempBucket->getValue(),distance));

			tempBucket = tempBucket->getNext();

			if(++flag == M) return queries;
          
        }
    }

    return queries;
}

set<int32_t> HyperCube::HammingDist(int32_t key , int probes ,int k){

	queue<pair<int32_t,int>> q;

	int32_t tempKey = key;

	set<int32_t> result;
	int32_t mask;
    
    int flag = pow(2,k);
    int count = 1;

    int startingPoint = 0;
	
    if(probes == 0) return result;

 	result.insert(key);
   
	if(probes == 1) return result;	

	while(++count != flag){

		for (int i=startingPoint ; i<k ; i++){

			mask = pow(2,i);
			int32_t newKey = tempKey^mask;
			
			q.push(make_pair(newKey,i+1));

			result.insert(newKey);

			if(result.size() == (unsigned long int)probes)
				return result;

			cout << endl;

		}

		tempKey = q.front().first;
		startingPoint = q.front().second;
		// cout << "tempKey became " << bitset<3>(tempKey) << endl;
	
		q.pop();

	}

	// result.insert(key);
	return result;
}


int HyperCube::coinFlip(){

	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0.01,1.99);

	return (int)distance(generator);
}

vector<item*> HyperCube::getItems(){
	return this->items;
}