#include "../headers/ContinuousLSH.h"

Continuous::Continuous(int k,int w,int L,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm){

	this->grid = new GridContinuous(delta);
	this->LSH = new Hash(k,w,L,size,dimension*2,"L2");
	this->M = 100000;
	this->epsilon = 0.5;
}

void Continuous::insert(item* i){

	item* originalItem = new item(*i);
	this->items.push_back(originalItem);

	item* hashedCurve = this->hashCurve(i);

	hashedCurve->setTrue(originalItem);

	// cout << "Inserting item with size " << hashedCurve->getVector()->size() << endl;

	this->LSH->insert(hashedCurve);
}

item* Continuous::hashCurve(item* i){

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
		if(tempVector->at(j) > min && tempVector->at(j) < tempVector->at(j+1))
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

	item* hashedItem = this->hashCurve(queryItem);

	pair<double,item*> results = (this->LSH->findkNN(1,hashedItem)).at(0);

	// // cout << "results.first is " << results.first << endl;

	// if(minimum > results.first){

	// 	minimum = results.first;
	// 	returnItem = results.second;
	// }

	// cout << endl << "RETURNING NOW " << minimum << endl << endl;
	return make_pair(results.first,results.second);
}
