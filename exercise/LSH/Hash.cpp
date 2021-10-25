#include "../headers/Hash.h"
#include "../headers/util.h"

Hash::Hash(int k,int L,int w,int size) : k(k), L(L), w(w), size(size) {

	for(int i=0;i<this->L;i++){

		HashTable *tempMap = new HashTable(size);
		hashTables.push_back(tempMap);
	}

	for(int i=0;i<k;i++)
		this->rVector.push_back((int32_t)rand());

}

Hash::~Hash(){}

void Hash::insert(item* newItem){

	this->items.push_back(newItem);

	for(int i=0;i<this->L;i++){

		int32_t temp = G(newItem,this->w,this->k,this->rVector,this->size);
		// cout << "Hashtable " << i << " inserting " << newItem->getID() << " in " << temp << endl;
		this->hashTables.at(i)->insert(temp , newItem );
	}

	// cout << endl;
}

void Hash::print(){

	for(int i=0;i<this->L;i++){

		// cout << "Hash table: " << i << ": " << endl;
		this->hashTables.at(i)->print();
		// cout << endl;
	}
}

pair<item*,double> Hash::findNN(item* queryItem){

	int minimum = numeric_limits<int>::max();
	pair<item*,double> b;
	double distance;
	int totalItems = 0;

	int32_t hash = G(queryItem,this->w,this->k,this->rVector,this->size);
	HashNode* tempBucket;	

	for(int i=0;i<this->L;i++){

		tempBucket = this->hashTables.at(i)->getBucket(hash);

		while(tempBucket != NULL){

			distance = dist(2,*queryItem,*tempBucket->getValue());
			if(distance < minimum){

				b = make_pair(tempBucket->getValue(),distance);
				minimum = distance;
			}
		
			if(++totalItems > 10*this->L) return b;

			tempBucket = tempBucket->getNext();
		}
	}

	return b;
}

vector<pair<double,item*> > Hash::findkNN(int k,item* queryItem){

	vector<pair<double,item*> > queries;
	int minimum = numeric_limits<int>::max();
	double distance;
	int totalItems = 0;

	int32_t hash = G(queryItem,this->w,this->k,this->rVector,this->size);
	HashNode* tempBucket;	

	for(int i=0;i<this->L;i++){

		tempBucket = this->hashTables.at(i)->getBucket(hash);

		while(tempBucket != NULL){

			//if(queryItem->getTrick() == tempBucket->getValue()->getTrick()){

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

			//}
			}
		
			if(totalItems > 10*this->L)
				return queries;
			
			tempBucket = tempBucket->getNext();
		}
	}

	return queries;
}

vector<pair<item*,double>> Hash::findRange(int r,item* queryItem){
    
    vector<pair<item*,double>> queries;

    int32_t hash = G(queryItem,this->w,this->k,this->rVector,this->size);
    //cout << "G is : " << G << endl;
    HashNode* tempBucket;

    double distance;

    int totalItems = 0;

    for (int i=0 ; i<this->L ; i++){

        tempBucket = this->hashTables.at(i)->getBucket(hash);
        
        while (tempBucket != NULL){
            
            //if(queryItem->getTrick() == tempBucket->getValue()->getTrick()){
            
  				if(!any_of(queries.begin(), queries.end(),[&tempBucket](const pair<item*,double>& p){ return p.first->getID() == tempBucket->getValue()->getID(); })){
              	
  					totalItems++;

	              	distance = dist(2,*queryItem,*tempBucket->getValue());
	                
	                if(distance < r)
	                    queries.push_back(make_pair(tempBucket->getValue(),distance));

	                if(queries.size() > (long unsigned int)20*this->L)
	                    return queries;

            	}
            //}

            if(totalItems > 20*this->L) return queries;

  			tempBucket = tempBucket->getNext();
          
        }
    }

    return queries;
}
