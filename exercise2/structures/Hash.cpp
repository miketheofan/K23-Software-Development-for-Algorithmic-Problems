#include "../headers/Hash.h"
#include "../headers/util.h"

Hash::Hash(int k,int L,int w,int size,int dimension) : k(k), L(L), w(w), size(size), dimension(dimension) {

	/* We create L hashTables inside the constructor and also L Gi which are the g functions that will be used
	for items hashing. */
	for(int i=0;i<this->L;i++){

		HashTable *tempMap = new HashTable(size);
		this->hashTables.push_back(tempMap);

		this->gVector.push_back(new Gi(k,dimension,w));
	}

}

Hash::~Hash(){

	for(vector<HashTable*>::iterator it = this->hashTables.begin(); it != this->hashTables.end(); it++)
		if(*it != NULL)
			delete *it;

	for(vector<Gi*>::iterator it = this->gVector.begin(); it != this->gVector.end(); it++)
		delete *it;

}

/* The following function inserts a given item to the Hash. */
void Hash::insert(item* newItem){

	/* First we insert the item in the items vector. */
	this->items.push_back(newItem);

	/* And then we also insert it in all L hash tables, using each's Gi hash function. */
	for(int i=0;i<this->L;i++){

		int32_t temp = this->gVector.at(i)->Hashi(newItem,this->size);
		this->hashTables.at(i)->insert(temp , newItem );
	}

}

void Hash::print(){

	for(int i=0;i<this->L;i++)
		this->hashTables.at(i)->print();
}

/* The following is our implementation for the k-Nearest Neigbours function. */
vector<pair<double,item*>> Hash::findkNN(int k,item* queryItem){

	vector<pair<double,item*>> results;
	vector<pair<double,item*>> queries;
	int minimum = numeric_limits<int>::max();
	double distance;
	int totalItems = 0;

	/* flag is used to indicate if search using ID trick didn't return enough items in order to answer query. In this case, 
	we search again without the help of ID trick. */
	bool flag = true;

	HashNode* tempBucket;	

	while(1){

		/* First we use the implementation that uses the ID trick. */
		if(flag == true){

			for(int i=0;i<this->L;i++){

				/* We hash the query item. */
				int32_t hash = this->gVector.at(i)->Hashi(queryItem,this->size);
				/* We get the bucket that corresponds to the calculated hash key. */
				tempBucket = this->hashTables.at(i)->getBucket(hash);

				/* Then we iterate through every item in bucket. */
				while(tempBucket != NULL){

					/* If they have the same ID */
					if(queryItem->getTrick() == tempBucket->getValue()->getTrick()){

						/* Calculate its' distance with query item. */
						distance = dist(2,*queryItem,*tempBucket->getValue());

						/* If it is lower than the previous minimum distance. */
						if(distance < minimum){

							/* And item does not already exists ( this is used because same item is inserted in all L hash tables so many buckets may 
							iterate through same item). */
							if(!any_of(queries.begin(), queries.end(),[&queryItem](const pair<double, item*>& p){ return p.second == queryItem; })){

								totalItems++;

								/* If vector is full (assuming that vector is sorted) */
								if((int)queries.size() == k){

									/* then we pop the last item (the one with the biggest distance) */
									queries.pop_back();
									/* and insert the new item in vector. */
									queries.push_back(make_pair(distance,tempBucket->getValue()));

									/* Then sort again for the next iteration. */
									sort(queries.begin(),queries.end());
									
									minimum	= distance;

								}else
									/* Otherwise just insert it. */
									queries.push_back(make_pair(distance,tempBucket->getValue()));
									sort(queries.begin(),queries.end());
							}

						}
					}
				
					/* Statement that was given in the paper in order to reduce the execution time of the program. */
					if(totalItems > 10*this->L)
						return queries;
					
					tempBucket = tempBucket->getNext();
				}

				results.insert(results.end(),queries.begin(),queries.end());
				sort(results.begin(),results.end());
				queries.clear();
			}

			/* If not enough items where inserted in the vector, then repeat process but this time without using the ID trick. */
			if(results.size() < (unsigned long)k) flag = false;
			else return results;

		}else{

			for(int i=0;i<this->L;i++){

				int32_t hash = this->gVector.at(i)->Hashi(queryItem,this->size);
				tempBucket = this->hashTables.at(i)->getBucket(hash);

				while(tempBucket != NULL){

					distance = dist(2,*queryItem,*tempBucket->getValue());

					if(distance < minimum){

						if(!any_of(queries.begin(), queries.end(),[&queryItem](const pair<double, item*>& p){ return p.second == queryItem; })){

							totalItems++;

							if((int)queries.size() == k){

								queries.pop_back();
								queries.push_back(make_pair(distance,tempBucket->getValue()));

								sort(queries.begin(),queries.end());
								
								minimum	= distance;

							}else
								queries.push_back(make_pair(distance,tempBucket->getValue()));
						}

					}
				
					if(totalItems > 10*this->L)
						return results;
					
					tempBucket = tempBucket->getNext();
				}

				results.insert(results.end(),queries.begin(),queries.end());
				sort(results.begin(),results.end());
				queries.clear();
			}

			return results;

		}
	}

	return results;
}

/* The following is our implementation for the range search function. */
vector<pair<item*,double>> Hash::findRange(int r,item* queryItem){
    
    vector<pair<item*,double>> queries;

    HashNode* tempBucket;

    double distance;

    int totalItems = 0;

    /* For every hash table. */
    for (int i=0 ; i<this->L ; i++){

		/* We hash the query item. */
 		int32_t hash = this->gVector.at(i)->Hashi(queryItem,this->size);
		/* We get the bucket that corresponds to the calculated hash key. */
       	tempBucket = this->hashTables.at(i)->getBucket(hash);
        
        /* Then we iterate through every item in bucket. */
        while (tempBucket != NULL){
               
            /* If item does not already exist */            
			if(!any_of(queries.begin(), queries.end(),[&tempBucket](const pair<item*,double>& p){ return p.first->getID() == tempBucket->getValue()->getID(); })){
          	
				totalItems++;

				/* Calculate query's item distance with this item */
              	distance = dist(2,*queryItem,*tempBucket->getValue());
                
                /* And if it is in range add it to the vector. */
                if(distance < r)
                    queries.push_back(make_pair(tempBucket->getValue(),distance));

                if(queries.size() > (long unsigned int)20*this->L)
                    return queries;

        	}

			/* Statement that was given in the paper in order to reduce the execution time of the program. */
            if(totalItems > 20*this->L) return queries;

  			tempBucket = tempBucket->getNext();
          
        }
    }

    return queries;
}

vector<item*> Hash::getItems(){
	return this->items;
}
