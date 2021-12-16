#include "../headers/ContinuousLSH.h"

Continuous::Continuous(int k,int w,int L,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm){

	this->grid = new GridContinuous(delta);
	this->LSH = new Hash(k,w,L,size,dimension*2,this->algorithm);
	this->M = 100000;
	this->epsilon = 0.5;
}

void Continuous::insert(item* i){

	item* originalItem = new item(*i);
	// this->items.push_back(originalItem);

	item* hashedCurve = this->hashCurve(i,originalItem);

	hashedCurve->setTrue(originalItem);
	this->items.push_back(hashedCurve);

	this->LSH->insert(hashedCurve);
}

vector<item*> Continuous::getItems(){
	return this->items;
}

item* Continuous::hashCurve(item* i,item* originalItem){

	item* newItem;

	// cout << "Size at first is " << i->getVector()->size() << endl;
	newItem = this->Filtering(i);
	// cout << "Size after filtering is " << newItem->getVector()->size() << endl;
	newItem = this->Snapping(newItem);
	// cout << "Size after snapping is " << newItem->getVector()->size() << endl;
	newItem = this->MinMax(newItem);
	// cout << "Size after minmax is " << newItem->getVector()->size() << endl;
	newItem = this->Padding(newItem);
	// cout << "Size after padding is " << newItem->getVector()->size() << endl;

	newItem->setTrue(originalItem);

	return newItem;
}

item* Continuous::Filtering(item* i){

	int count =0;

	vector<double> newVector;
	vector<double>* tempVector = i->getVector();

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

item* Continuous::Snapping(item* i){
	return this->grid->Hashing(i);
}

item* Continuous::MinMax(item* i){

	vector<double> newVector;
	vector<double>* tempVector = i->getVector();

	if(tempVector->size() == 0)
		return i;

	double min = tempVector->at(0);
	newVector.push_back(min);

	// cout << "The deadly line is " << tempVector->size() << endl;

	for(int j=1;j<(int)tempVector->size();j++){

		if(j == (int)tempVector->size() -1){

			newVector.push_back(tempVector->at(j));
			break;
		}

		// min = tempVector->at(j);
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

item* Continuous::Padding(item* i){

	if(i->getVector()->size() == (unsigned long int)this->dimension)
		return i;
	
	int diff = (this->dimension) - (i->getVector()->size());

	for(int y=0;y<diff;y++)
		i->addCoordinate(this->M);
	
	return i;

}

pair<double,item*> Continuous::findNN(item* queryItem){

	// double minimum = numeric_limits<double>::max();
	// item* returnItem;

	item* hashedItem = this->hashCurve(queryItem,queryItem);

	pair<double,item*> results = (this->LSH->findkNN(1,hashedItem)).at(0);

	// // cout << "results.first is " << results.first << endl;

	// if(minimum > results.first){

	// 	minimum = results.first;
	// 	returnItem = results.second;
	// }

	// cout << endl << "RETURNING NOW " << minimum << endl << endl;
	return make_pair(results.first,results.second);
}

pair<double,item*> Continuous::findNNbrute(item* queryItem){

	// cout << "Entered for query item with size " << queryItem->getDimension() << endl;

	double minimum = numeric_limits<double>::max();
	item* returnItem;	
	
	// queryItem->setTrue(queryItem);
	const Curve& tempCurve = queryItem->Camouflage();

	for(vector<item*>::iterator it = this->items.begin();it != this->items.end(); it++){

		// cout << "query's dimension is " << queryItem->getDimension() << endl;
		// cout << "current item's dimension is " << (*it)->getDimension() << endl;

		// queryItem->print();

		double distance = Frechet::Continuous::distance((*it)->Camouflage(),tempCurve).value;
		// cout << "Distance is " << distance << endl;
		// distance = Frechet::Continuous::distance(queryItem->Camouflage(),tempBucket->getValue()->Camouflage()).value;

		if(minimum > distance){

			// cout << "Got here" << endl;
			minimum = distance;
			returnItem = *it;
		}
	}

	// cout << "Ending" << endl;
	return make_pair(minimum,returnItem);
}

vector<pair<item*,double>> Continuous::rangeSearch(int r,item* queryItem){

	// item* hashedItem = this->hashCurve(queryItem,queryItem);
	vector<pair<item*,double>> hashedItems = this->LSH->findRange(r,this->hashCurve(queryItem,queryItem));
	vector<pair<item*,double>> originalItems;


	for(vector<pair<item*,double>>::iterator it = hashedItems.begin();it != hashedItems.end(); it++)
		originalItems.push_back(make_pair((*it).first,(*it).second));

	return originalItems;
}