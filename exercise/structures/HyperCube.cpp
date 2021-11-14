#include "../headers/HyperCube.h"
#include "../headers/utilCUBE.h"

HyperCube::HyperCube(int k,int w,int M,int probes,int dimension) : k(k), w(w), M(M), probes(probes), dimension(dimension) {

	this->cube = new HashTable(pow(2,this->k));

	/* We create k edges for the hyper cube that will be used to store the items. */
	for(int i=0;i<this->k;i++){

		unordered_map<int32_t,int> temp;
		this->fVector.push_back(temp);
	}

	/* We also create k Hi functions that will be used to hash the items in order to insert them in the corresponding edge. */
	for(int i=0;i<this->k;i++)
		this->hVector.push_back(new Hi(dimension,w));
}

HyperCube::~HyperCube(){

	for(vector<Hi*>::iterator it = this->hVector.begin(); it != this->hVector.end(); it++)
		delete *it;

	delete this->cube;
}

/* The following function is used to insert given item in HyperCube. */
void HyperCube::insert(item *it){

	this->items.push_back(it);

	this->cube->insert(this->hashFunction(it),it);
}

/* The following is the hash function of the HyperCube. */
int32_t HyperCube::hashFunction(item* it){

	int32_t key = 0;

	/* We use each of the k Hi functions and flip a coin in order to transform the result of Hi to either 0 or 1. */
	for(int i=0;i<this->k;i++){

		int32_t hash = this->hVector.at(i)->Hashi(it);

		/* If Hi's result has already been produced, then we use its' previous coin flip. */
		if(fVector.at(i).find(hash) == fVector.at(i).end())
			fVector.at(i)[hash] = coinFlip();

		/* We put the bit in the key. */
		key = key << 1;
		key = key | fVector.at(i)[hash];
	}
	
	return key;
}

/* The following is our implementation for the k-Nearest Neigbours function. */
vector<pair<double,item*>> HyperCube::findkNN(item* queryItem,int M,int k){

	double minimum = numeric_limits<int>::max();

	vector<pair<double,item*>> results;

	/* We hash the query item. */
	int32_t hash = this->hashFunction(queryItem);

	int flag =0;

	HashNode* tempBucket;

	/* Then we get the bucket that corresponds to the hash key produced and also the probes-closest buckets. */
	set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k);

	/* For every bucket */
	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		tempBucket = this->cube->getBucket(*i);

		/* We iterate through all items in bucket */
		while(tempBucket != NULL){

			flag++;

			double distance = dist(2,*queryItem,*tempBucket->getValue());

			/* If distance is greater than the minimum distance (distance of last item's in vector). */
			if(isgreater(minimum,distance)){

				/* If vector is full (assuming that vector is sorted) */
				if((int)results.size() == k){

					/* then we pop the last item (the one with the biggest distance) */
					results.pop_back();
					/* and insert the new item in vector. */
					results.push_back(make_pair(distance,tempBucket->getValue()));

					/* Then sort again for the next iteration. */
					sort(results.begin(),results.end());
					
					minimum	= results.at(results.size()-1).first;

				}else{

					/* Otherwise just insert it. */
					results.push_back(make_pair(distance,tempBucket->getValue()));
					sort(results.begin(),results.end());
				}
			}

			/* Statement that was given in the paper in order to reduce the execution time of the program. */
			tempBucket = tempBucket->getNext();

			if(++flag == M) return results;

		}
	}

	return results;
}

/* The following is our implementation for the range search function. */
vector<pair<item*,double>> HyperCube::findRange(int r,item* queryItem,int M){

	vector<pair<item*,double>> queries;

	/* We hash the query item. */
	int32_t hash = this->hashFunction(queryItem);
    HashNode* tempBucket;

    int flag = 0;

    double distance;

 	/* Then we get the bucket that corresponds to the hash key produced and also the probes-closest buckets. */
   	set<int32_t> nearVertices = this->HammingDist(hash,this->probes,this->k);

	/* For every bucket */
	for(auto i = nearVertices.begin();i != nearVertices.end();i++){

		tempBucket = this->cube->getBucket(*i);

		/* We iterate through all items in bucket */
		while(tempBucket != NULL){
                              	
	      	distance = dist(2,*queryItem,*tempBucket->getValue());
	        
            /* And if it is in range add it to the vector. */
	        if(isgreater(r,distance))
	            queries.push_back(make_pair(tempBucket->getValue(),distance));

			tempBucket = tempBucket->getNext();

			/* Statement that was given in the paper in order to reduce the execution time of the program. */
			if(++flag == M) return queries;
          
        }
    }

    return queries;
}

/* The following function uses hamming distance in order to return probes-closest edges from given edge. */
set<int32_t> HyperCube::HammingDist(int32_t key , int probes ,int k){

	queue<pair<int32_t,int>> q;

	int32_t tempKey = key;

	set<int32_t> result;
	int32_t mask;
    
    /* Flag is used to store the total amount of edges that can be produced given the amount of bits that a number must have. */
    int flag = pow(2,k);
    int count = 1;

    int startingPoint = 0;
	
	/* If probes is zero then return empty vector. */
    if(probes == 0) return result;

 	result.insert(key);
   
   	/* If probes is one then return only the starting key. */
	if(probes == 1) return result;	

	/* For every number that can possibly be produced. */
	while(++count != flag){

		/* For every one of its k bits. */
		for (int i=startingPoint ; i<k ; i++){

			/* Change the bit */
			mask = pow(2,i);
			int32_t newKey = tempKey^mask;
			
			/* And push it to the queue. */
			q.push(make_pair(newKey,i+1));

			/* Also put it in the return vector. */
			result.insert(newKey);

			/* If we have produced probes-numbers then return. */
			if(result.size() == (unsigned long int)probes)
				return result;

			cout << endl;

		}

		/* Otherwise just pop a number from the queue and repeat the process with it. */
		tempKey = q.front().first;
		startingPoint = q.front().second;
	
		q.pop();

	}

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