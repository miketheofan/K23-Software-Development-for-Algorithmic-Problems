#include "../headers/DiscreteLSH.h"
#include "../headers/util.h"

Discrete::Discrete(int k,int w,int L,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm) {

	// this->LSH = new Hash(k,w,L,size,dimension*2);

	for(int i=0;i<L;i++){

		this->grids.push_back(new Grid(delta));
		this->LSH.push_back(new Hash(k,w,L,size,dimension*2,this->algorithm));
	}

	this->M = 100000;
}

void Discrete::insert(item* i){

	// cout << "Entered for ";
	// i->print();cout << endl;

	// this->items.push_back(i);
	
	// Curve* newCurve;
	item* newItem;
	
	for(int y=0;y<this->L;y++){

		// newCurve = this->Polygonization(i);
		// // newCurve->print();
		// newCurve = this->Snapping(newCurve,y);
		// // cout << "Got here" << endl;
		// newItem = this->Vectorization(newCurve,i);
		// this->Padding(newItem,newCurve);

		newItem = this->hashCurve(i,y,true);

		// cout << "Inserting in LSH item ";
		// newItem->print();cout << endl;

		this->LSH.at(y)->insert(newItem);
		// cout << "Inserted " << newItem->getID() << " in Hash table " << y << endl;
	}
}

item* Discrete::hashCurve(item* i,int y,bool insert){

	Curve* newCurve,*originalCurve;
	item* newItem;

	newCurve = this->Polygonization(i);

	if(insert) this->items.push_back(newCurve);

	originalCurve = new Curve(*newCurve);
	// cout << "Original curve is ";
	// newCurve->print();
	// newCurve->print();
	newCurve = this->Snapping(newCurve,y);
	// cout << "Snapping returned ";newCurve->print();
	newItem = this->Vectorization(newCurve,i);
	// cout << "Vectorization returned ";newItem->print();
	newItem = this->Padding(newItem,originalCurve);
	// cout << "Padding returned ";newItem->print();

	// cout << "Hashed item " << newItem->getID() << " with curve " << newItem->getCurve()->getID() << endl;

	return newItem;
}

Curve* Discrete::Snapping(Curve* curve,int index){
  	return this->grids.at(index)->Hashing(curve);
}

Curve* Discrete::Polygonization(item* i){

	int counter =0;

	Curve* tempCurve = new Curve(i->getID());

	for(vector<double>::iterator it = i->getVector()->begin();it != i->getVector()->end();it++){

		vector<double> temp;
	
		temp.push_back(++counter);
		// cout << "Inserted " << counter << " in curve " << i->getID() << endl;
		temp.push_back(*it);
		// cout << "Inserted " << (*it) << " in curve " << i->getID() << endl;
		tempCurve->addCoordinate(new item(i->getID(),temp));
	}
	
	// tempCurve->addCoordinate(new item(i->getID(),temp));
	
	return tempCurve;
}

item* Discrete::Vectorization(Curve* i,item* original){

	// item* newItem;
	vector<double> temp;

	for(vector<item*>::iterator it = i->getCoordinates()->begin();it != i->getCoordinates()->end(); it++){

		temp.push_back((*it)->getCoordinatein(0));
		temp.push_back((*it)->getCoordinatein(1));
	}

	item* newItem = new item(original->getID(),temp);
	newItem->setTrue(original);

	return newItem;
}

item* Discrete::Padding(item* i,Curve* curve){

	if(i->getVector()->size() == (unsigned long int)this->dimension*2){

		i->setCurve(curve);
		return i;
	}

	int diff = (this->dimension) - (curve->getSize());

	// cout << "Dimension is " << this->dimension << " size of curve is " << curve->getSize() << endl;
	// cout << "Difference for " << i->getID() << " is " << diff << endl;

	for(int y=0;y<diff;y++){

		i->addCoordinate(this->M);

		vector<double> temp;
		temp.push_back(this->M);
		temp.push_back(this->M);

		curve->addCoordinate(new item(i->getID(),temp));
	}

	// cout << "Original curve's size of " << curve->getID() << " is " << curve->getSize() << endl;
	i->setCurve(curve);
	// cout << "Set curve is ";
	// curve->print();

	return i;
}

pair<double,Curve*> Discrete::findNN(item* queryItem){

	double minimum = numeric_limits<double>::max();
	item* returnItem;

	for(int i=0;i<this->L;i++){

		item* hashedItem = this->hashCurve(queryItem,i,false);

		pair<double,item*> results = (this->LSH.at(i)->findkNN(1,hashedItem)).at(0);

		// cout << "results.first is " << results.first << endl;

		if(minimum > results.first){

			minimum = results.first;
			returnItem = results.second;
		}
	}

	// cout << endl << "RETURNING NOW " << minimum << endl << endl;
	return make_pair(minimum,returnItem->getCurve());
}

pair<double,Curve*> Discrete::findNNbrute(item* queryItem){

	double minimum = numeric_limits<double>::max();
	Curve* returnItem;	
	
	for(vector<Curve*>::iterator it = this->items.begin();it != this->items.end(); it++){

		// cout << "Starting with curve:" << endl;
		// (*it)->print();

		int distance = distFrechetBrute((*it),this->Polygonization(queryItem));

		if(minimum > distance){

			// cout << "Got here" << endl;
			minimum = distance;
			returnItem = *it;
		}
	}

	cout << "Ending" << endl;
	return make_pair(minimum,returnItem);
}
