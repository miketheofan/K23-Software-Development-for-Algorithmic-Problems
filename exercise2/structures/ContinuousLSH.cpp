#include "../headers/ContinuousLSH.h"

Continuous::Continuous(int k,int w,int L,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm){

	this->grid = new GridContinuous(delta);
	this->LSH = new Hash(k,w,L,size,dimension*2,this->algorithm);

	/* We initialize M as a big number, in order not to have a big effect on the following calcultions. */
	this->M = 100000;
	this->epsilon = 0.5;
}

Continuous::~Continuous(){

	delete this->grid;
	delete this->LSH;
}

/* The following function inserts a Point to the Continuous LSH structure. */
void Continuous::insert(item* i){

	/* We keep the original item. */
	item* originalItem = new item(*i);

	/* We hash the Point. */
	item* hashedCurve = this->hashCurve(i,originalItem);

	/* We set the hashed point's original Point as the given as paramter one. */
	hashedCurve->setTrue(originalItem);
	this->items.push_back(hashedCurve);

	/* And then we insert it in the structure. */
	this->LSH->insert(hashedCurve);
}

vector<item*> Continuous::getItems(){
	return this->items;
}

/* The following is the hash function which hashes any point given in order for it to be able to enter the LSH structure. */
item* Continuous::hashCurve(item* i,item* originalItem){

	item* newItem;

	newItem = this->Filtering(i);
	newItem = this->Snapping(newItem);
	newItem = this->MinMax(newItem);
	newItem = this->Padding(newItem);

	newItem->setTrue(originalItem);

	return newItem;
}

/* The following is our implementation for the filtering algorithm. */
item* Continuous::Filtering(item* i){

	int count =0;

	vector<double> newVector;
	vector<double>* tempVector = i->getVector();

	/* We basically keep a new vector, in which every Point that is not close to its previous and its next one is entered.
		Finally we set the item's given vector of coordinates, as the new vector. */

	for(int j=0;j<(int)tempVector->size();j++){

		if(j == (int)tempVector->size() -1){

			newVector.push_back(tempVector->at(j));
			break;
		}

		if(!count++) continue;

		if( abs(tempVector->at(j)-tempVector->at(j-1)) < this->epsilon && abs(tempVector->at(j)-tempVector->at(j+1)) < this->epsilon)
			continue;
		
		newVector.push_back(tempVector->at(j));
	}

	i->setVector(newVector);

	return i;
}

/* The following is our implementation for the Snapping algorithm. It used the grid's Hashing function which is found in GridContinuous.cpp. */
item* Continuous::Snapping(item* i){
	return this->grid->Hashing(i);
}

/* The following is our impelementation for the MinMax algorithm. */
item* Continuous::MinMax(item* i){

	vector<double> newVector;
	vector<double>* tempVector = i->getVector();

	if(tempVector->size() == 0)
		return i;

	double min = tempVector->at(0);
	newVector.push_back(min);

	/* Again, we use a new vector where we store all points that are not inside extrenums of the curve. For example,
		if we had a curve: [0,1,3,5,2], we would keep [0,5,2] to the new vector, and then set it as the Point's given vector. */

	for(int j=1;j<(int)tempVector->size();j++){

		if(j == (int)tempVector->size() -1){

			newVector.push_back(tempVector->at(j));
			break;
		}

		if(tempVector->at(j) >= min && tempVector->at(j) <= tempVector->at(j+1))
			continue;
		else{

			min = tempVector->at(j) < min;
			newVector.push_back(tempVector->at(j));
		}
	}

	i->setVector(newVector);

	return i;
}

/* The following is our implementation for the Padding algorithm. */
item* Continuous::Padding(item* i){

	if(i->getVector()->size() == (unsigned long int)this->dimension)
		return i;
	
	int diff = (this->dimension) - (i->getVector()->size());

	/* For any coordinates that are missing in order for the Point to have this->dimension coordinates,
	we add M as a coordinate. */
	for(int y=0;y<diff;y++)
		i->addCoordinate(this->M);
	
	return i;

}

/* The following is the function that returns the nearest neigbour from the query point given. */
pair<double,item*> Continuous::findNN(item* queryItem){

	item* hashedItem = this->hashCurve(queryItem,queryItem);

	pair<double,item*> results = (this->LSH->findkNN(1,hashedItem)).at(0);

	return make_pair(results.first,results.second);
}

/* The following is a function that returns the nearest neigbour from query point, using the brute way. It compares
the continuous distance from the query Point to all the rest points. */
pair<double,item*> Continuous::findNNbrute(item* queryItem){

	double minimum = numeric_limits<double>::max();
	item* returnItem;	
	
	const Curve& tempCurve = queryItem->Camouflage();

	for(vector<item*>::iterator it = this->items.begin();it != this->items.end(); it++){

		double distance = Frechet::Continuous::distance((*it)->Camouflage(),tempCurve).value;

		if(minimum > distance){

			minimum = distance;
			returnItem = *it;
		}
	}

	return make_pair(minimum,returnItem);
}

/* The following is a function that returns all points that are in range r from query Point. */
vector<pair<item*,double>> Continuous::rangeSearch(int r,item* queryItem){

	vector<pair<item*,double>> hashedItems = this->LSH->findRange(r,this->hashCurve(queryItem,queryItem));
	vector<pair<item*,double>> originalItems;

	/* We return the original curve of each item that was returned from LSH::findRange. */
	for(vector<pair<item*,double>>::iterator it = hashedItems.begin();it != hashedItems.end(); it++)
		originalItems.push_back(make_pair((*it).first,(*it).second));

	return originalItems;
}