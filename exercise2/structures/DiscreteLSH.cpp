#include "../headers/DiscreteLSH.h"
#include "../headers/util.h"

Discrete::Discrete(int k,int w,int L,int size,int dimension,int delta,string algorithm) : dimension(dimension), delta(delta), L(L), algorithm(algorithm) {

	for(int i=0;i<L;i++){

		this->grids.push_back(new Grid(delta));
		this->LSH.push_back(new Hash(k,w,L,size,dimension*2,this->algorithm));
	}

	/* We initialize M as a big number, in order not to have a big effect on the following calcultions. */
	this->M = 100000;
}

Discrete::~Discrete(){

	for(vector<curve*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		delete (*it);

	for(vector<Grid*>::iterator it = this->grids.begin(); it != this->grids.end(); it++)
		delete (*it);

	for(vector<Hash*>::iterator it = this->LSH.begin(); it != this->LSH.end(); it++)
		delete (*it);
}

/* The following function inserts a Point to discrete LSH structure. */
void Discrete::insert(item* i){

	item* newItem;
	
	/* It hashes the Point, and then inserts it to each of the L LSH structures. */
	for(int y=0;y<this->L;y++){

		newItem = this->hashCurve(i,y,true);

		this->LSH.at(y)->insert(newItem);
	}
}

vector<item*> Discrete::getItems(){

	vector<item*> tempVector;
	for(vector<curve*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		tempVector.push_back((*it)->getOriginal());

	return tempVector;
}

/* The following function hashed a Point given. */
item* Discrete::hashCurve(item* i,int y,bool insert){

	curve* newCurve,*originalCurve;
	item* newItem;

	newCurve = this->Polygonization(i);

	/* The following condition checks if function was called while inserting an item or while finding nearest neigbour. */
	if(insert){ 
	
		newCurve->setOriginal(i);
		this->items.push_back(newCurve);
	}
	originalCurve = new curve(*newCurve);
	newCurve = this->Snapping(newCurve,y);
	newItem = this->Vectorization(newCurve,i);
	newItem = this->Padding(newItem,originalCurve);

	return newItem;
}

/* The following is our implementation for the Snapping algorithm. It used the grid's Hashing function which is found in Grid.cpp. */
curve* Discrete::Snapping(curve* c,int index){
  	return this->grids.at(index)->Hashing(c);
}

/* The following is our implementation for the Polygonization algorithm. */
curve* Discrete::Polygonization(item* i){

	int counter =0;

	curve* tempCurve = new curve(i->getID());

	/* It creates a new Curve and inserts every coordinate of the Point, while condidering the axis of time.
		For example, if he had a Point [1,2,3], we will now have a Curve [(1,1),(2,2),(3,3)]. */
	for(vector<double>::iterator it = i->getVector()->begin();it != i->getVector()->end();it++){

		vector<double> temp;
	
		temp.push_back(++counter);
		temp.push_back(*it);
		tempCurve->addCoordinate(new item(i->getID(),temp));
	}
		
	return tempCurve;
}

/* The following is our implementation for the Vectorization algorithm. */
item* Discrete::Vectorization(curve* i,item* original){

	vector<double> temp;

	/* We create a new vector where we insert all coordinates from both dimensions accordingly. */
	for(vector<item*>::iterator it = i->getCoordinates()->begin();it != i->getCoordinates()->end(); it++){

		temp.push_back((*it)->getCoordinatein(0));
		temp.push_back((*it)->getCoordinatein(1));
	}

	item* newItem = new item(original->getID(),temp);
	newItem->setTrue(original);

	return newItem;
}

/* The following is our implementation for the Padding algorithm. */
item* Discrete::Padding(item* i,curve* c){

	if(i->getVector()->size() == (unsigned long int)this->dimension*2){

		i->setCurve(c);
		return i;
	}

	int diff = (this->dimension) - (c->getSize());

	/* For any coordinates that are missing in order for the Point to have this->dimension coordinates,
	we add M as a coordinate. */
	for(int y=0;y<diff;y++){

		i->addCoordinate(this->M);

		vector<double> temp;
		temp.push_back(this->M);
		temp.push_back(this->M);

		c->addCoordinate(new item(i->getID(),temp));
	}

	i->setCurve(c);

	return i;
}

/* The following is the function that returns the nearest neigbour from the query point given. */
pair<double,curve*> Discrete::findNN(item* queryItem){

	double minimum = numeric_limits<double>::max();
	item* returnItem;

	for(int i=0;i<this->L;i++){

		item* hashedItem = this->hashCurve(queryItem,i,false);

		pair<double,item*> results = (this->LSH.at(i)->findkNN(1,hashedItem)).at(0);

		if(minimum > results.first){

			minimum = results.first;
			returnItem = results.second;
		}
	}

	return make_pair(minimum,returnItem->getCurve());
}

/* The following is a function that returns the nearest neigbour from query point, using the brute way. It compares
the discrete distance from the query Point to all the rest points. */
pair<double,curve*> Discrete::findNNbrute(item* queryItem){

	double minimum = numeric_limits<double>::max();
	curve* returnItem;	
	
	for(vector<curve*>::iterator it = this->items.begin();it != this->items.end(); it++){

		int distance = distFrechetBrute((*it),this->Polygonization(queryItem));

		if(minimum > distance){

			minimum = distance;
			returnItem = *it;
		}
	}

	return make_pair(minimum,returnItem);
}

/* The following is a function that returns all points that are in range r from query Point. */
vector<pair<item*,double>> Discrete::rangeSearch(int r,item* queryItem){

	vector<pair<item*,double>> final;

	for(int i=0;i<this->L;i++){

		vector<pair<item*,double>> results = (this->LSH.at(i)->findRange(r,this->hashCurve(queryItem,i,false)));
		final.insert(final.end(),results.begin(),results.end());
	}

	return final;
}
