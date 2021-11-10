#include "../headers/Cluster.h"
#include "../headers/utilCLUSTER.h"

#include "../headers/Cluster.h"
#include "../headers/utilCLUSTER.h"


Cluster::Cluster(item* centroid){

	this->centroid = new item(*centroid);
	this->dimension = this->centroid->getDimension();
	this->items.push_back(centroid);
}

Cluster::~Cluster(){
	delete this->centroid;
}

item* Cluster::getCentroid(){
	return this->centroid;
}

void Cluster::insert(item* it){
	this->items.push_back(it);
}

int Cluster::print(){
	return this->items.size();
}

pair<string,vector<string>> Cluster::getCompleteCluster(){

	vector<string> ids;

	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		ids.push_back((*it)->getID());

	return make_pair(this->centroid->getID(),ids);
}

bool Cluster::Update(){

	bool flag = false;

	double T = this->items.size();
	double sum = 0;

	vector<double> newCoordinates;

	// int dimension = this->dimension;

	for(int i=0; i<this->dimension; i++){
		// cout << "Got here" << endl;

		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
			sum += (*it)->getCoordinatein(i);
	
		double Mean = sum / T;

		// cout << "Got out" << endl;
		newCoordinates.push_back(Mean);

		sum = 0;

	}

	if(*(this->centroid->getVector()) == newCoordinates)
		flag = true;

	delete this->centroid;
	this->centroid = new item("newItem",newCoordinates);

	// cout << "New centroid is ";
	// this->centroid->print();cout << endl;

	// this->items.clear();

	// cout << "Returning" << endl;

	return flag;
}

void Cluster::clearCluster(){
	this->items.clear();
}

int Cluster::getDimension(){
	return this->dimension;
}

void Cluster::deleteItem(item *i){

	vector<item*>::iterator toDelete = find(this->items.begin(),this->items.end(),i);
	
	if(toDelete != this->items.end())
		this->items.erase(toDelete);
	else
		i->setFlag(-1);
}

bool Cluster::exists(item *i){

	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		if((i->getID() == (*it)->getID()))
			return true;

	return false;
}

vector<item*> Cluster::getItems(){
	return this->items;
}

Clustering::Clustering(int K,int L,int kLSH,int M,int kCUBE,int probes,int w, int totalItems)
: K(K), L(L), kLSH(kLSH), M(M), kCUBE(kCUBE), probes(probes), w(w), totalItems(totalItems) {


}

Clustering::~Clustering(){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
	delete *it; 
}

int Clustering::noItems(){
	return this->items.size();
}

void Clustering::insert(item* item){
	this->items.push_back(item);
}

vector<Cluster*> Clustering::getClusters(){
	return this->clusters;
}

pair<int,item*> Clustering::getClusterat(int index){

	Cluster *tmp = this->clusters.at(index);
	int size = tmp->getItems().size();
	item *centoid = tmp->getCentroid();

	return make_pair(size,centoid);
}

pair<string,vector<string>> Clustering::getCompleteClusterat(int index){
	return this->clusters.at(index)->getCompleteCluster();
}


void Clustering::kMeansPP(){

	int t =0;

	vector<item*> chosenCentroids;

	//vector<pair<item*,double> > array;

	item* firstCentroid = getRandomItem(this->items);

	chosenCentroids.push_back(firstCentroid);
	// deleteByValue(firstCentroid,&this->items);
	this->clusters.push_back(new Cluster(firstCentroid));

	t++;

	double minimum = numeric_limits<double>::max();
	item *minCentroid = NULL;

	vector<pair<double,item*>> P;

	while(t < this->K){

		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

			// for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			// 	double distance = dist(2,**it,*(*it2)->getCentroid());

			// 	if( distance < minimum ){

			// 		minimum = distance;
			// 		minCentroid = (*it2)->getCentroid();
			// 	}
			// }

			// D.push_back(make_pair(*it,minimum));

			double sum =0;

			for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

				double distance = dist(2,**it,*(*it2)->getCentroid());
				distance = pow(distance,2);
				
				sum += distance;
			}

			P.push_back(make_pair(sum,*it));

		}
		sort(P.begin(),P.end());
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(0,P.at(P.size()-1).first);

		double temp = dis(gen);
		vector<pair<double,item*>>::iterator it3;
		for(it3 = P.begin() ; it3 != P.end() ; it3++)
			if((*it3).first >= temp) break;

		this->clusters.push_back(new Cluster((*it3).second));

		t++;
	}
}

void Clustering::Assign(string assignMethod){

	Hash *h;
	HyperCube *c;

	if(assignMethod == "LSH"){

		h = new Hash(this->kLSH, this->L, this->w, this->totalItems/4,this->clusters.at(0)->getDimension());
		this->fillHash(h);
	}

	if(assignMethod == "Hypercube"){

		c = new HyperCube(this->kCUBE, this->w,this->M,this->probes,this->clusters.at(0)->getDimension());
		this->fillCube(c);
	}

	while(1){

		this->clearClusters();

		if(assignMethod == "Classic")
			this->Lloyd();
		else if(assignMethod == "LSH")
			this->LSH(h);
		else if(assignMethod == "Hypercube")
			this->Hypercube(c);	
		else{

			cerr << "Not valid assignment method given." << endl;
			return;
		}

		if(this->Update() == 1)
			break;

	}

	if(assignMethod == "LSH") delete h;
	if(assignMethod == "Hypercube") delete c;
}

void Clustering::Lloyd(){

	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

		double minimum = numeric_limits<double>::max();

		Cluster *minCluster;

		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			int distance = dist(2,**it,*(*it2)->getCentroid());

			// cout << "Distance from " << ++count << " is " << distance << endl;

			// cout << "Item's " << (*it)->getID() << " distance from cluster " << count++ << " is " << distance << endl; 

			if( distance < minimum ){

				minimum = distance;
				minCluster = *it2;
			}
		}

		// cout << endl;

		minCluster->insert(*it);

	}
}

void Clustering::LSH(Hash *h){

	double range = this->minDistCentroids()/2;
	// cout << "Range is " << range << endl;

	// Hash *h = new Hash(this->kLSH, this->L, this->w, this->totalItems/4,this->clusters.at(0)->getDimension());
	// this->fillHash(h);

	int totalItems = h->getItems().size();

	int pos = 0;

	int endCond = -1;
	int lastendCond = 0;
	// int totalItems = this->items.size();

	vector<pair<item*,double>> temp;

	while(endCond != lastendCond){

		lastendCond = endCond;
		endCond = 0;

		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

			temp = h->findRange(range,(*it)->getCentroid());

			// cout << "Returned items: " << temp.size() << endl;

			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
								
				// cout << "Entered here" << endl;

				if( (*it2).first->getFlag() == -1 ){
					
					// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;

					(*it)->insert(it2->first);
					(*it2).first->setFlag(pos);
					endCond++;

				}else{

					item *newCentroid = (*it)->getCentroid();
					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

					double distanceNew = dist(2,*(*it2).first,*newCentroid);
					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

					if( distanceNew < distanceOld ){

						// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;
						
						(this->clusters.at((*it2).first->getFlag())->deleteItem((*it2).first));
						(*it)->insert(it2->first);
						(*it2).first->setFlag(pos);

						endCond++;
					}
				}
			}

			if( (long unsigned int)(++pos) == this->clusters.size())
				pos = 0;
			
		}

		range *= 2; 
	
	}

	this->assignRest(h->getItems());

	// delete h;
}

void Clustering::Hypercube(HyperCube *c){

	double range = this->minDistCentroids()/2;
	// cout << "Range is " << range << endl;

	// HyperCube *c = new HyperCube(this->kCUBE, this->w,this->M,this->probes,this->clusters.at(0)->getDimension());
	// this->fillCube(c);

	// int totalItems = c->getItems().size();

	int pos = 0;

	int endCond = -1;
	int lastendCond = 0;
	// int totalItems = this->items.size();

	vector<pair<item*,double>> temp;

	while(endCond != lastendCond){

		// cout << "Range is " << range << endl;
		// cout << "Got here" << " with endCond " << endCond << endl;

		lastendCond = endCond;
		endCond = 0;

		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

			temp = c->findRange(range,(*it)->getCentroid(),this->M);

			// cout << "Returned items: " << temp.size() << endl;

			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
				
				// cout << "Entered here" << endl;

				if( (*it2).first->getFlag() == -1 ){
					
					// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;

					(*it)->insert(it2->first);
					(*it2).first->setFlag(pos);
					endCond++;

				}else{

					item *newCentroid = (*it)->getCentroid();
					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

					double distanceNew = dist(2,*(*it2).first,*newCentroid);
					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

					if( distanceNew < distanceOld ){

						// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;
						
						(this->clusters.at((*it2).first->getFlag())->deleteItem((*it2).first));
						(*it)->insert(it2->first);
						(*it2).first->setFlag(pos);

						endCond++;
					}
				}
			}

			if( (long unsigned int)(++pos) == this->clusters.size())
				pos = 0;
			
		}

		range *= 2; 
	
	}

	this->assignRest(c->getItems());

	// delete c;

}

void Clustering::assignRest(vector<item*> items){

	for(vector<item*>::iterator it = items.begin(); it != items.end(); it++){

		// if((*it)->getFlag() != -1) continue;

		if(this->exists(*it)) continue;

		double minimum = numeric_limits<double>::max();

		Cluster *minCluster;

		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			int distance = dist(2,**it,*(*it2)->getCentroid());

			// cout << "Distance from " << ++count << " is " << distance << endl;

			// cout << "Item's " << (*it)->getID() << " distance from cluster " << count++ << " is " << distance << endl; 

			if( distance < minimum ){

				minimum = distance;
				minCluster = *it2;
			}
		}

		// cout << endl;

		// cout << "Inserting item " << (*it)->getID() << " with flag " << (*it)->getFlag() << endl;
		minCluster->insert(*it);
	}
}

double Clustering::Update(){

	double count = 0;

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		if((*it)->Update() == true)
			count++;

	// cout << "Syspro" << endl;
	// cout << "Size is " << this->clusters.size();

	return count/this->clusters.size();	
}

void Clustering::clearClusters(){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		(*it)->clearCluster();
}

void Clustering::print(){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		cout << "Size: " << (*it)->print() << endl;
}

void Clustering::fillCube(HyperCube* cube){

	for (vector<item*>::iterator i = items.begin() ; i!=items.end() ; i++)
		cube->insert(*i);
}

void Clustering::fillHash(Hash* hash){

	for(vector<item*>::iterator i = items.begin() ; i!=items.end() ; i++)
		hash->insert(*i);
}

double Clustering::minDistCentroids(){
	
	double minimum = numeric_limits<double>::max();

	for(unsigned long int i=0; i < this->clusters.size(); i++)
		for(unsigned long int j=0; j < this->clusters.size(); j++){

			if( i == j ) continue;

			// cout << "Comparing centroid: ";
			// this->clusters.at(i)->getCentroid()->print();
			// cout << endl << " with centroid: ";
			// this->clusters.at(j)->getCentroid()->print();cout << endl;

			double distance = dist(2,*this->clusters.at(i)->getCentroid(),*this->clusters.at(j)->getCentroid());

			if(distance < minimum)
				minimum = distance;

		}

	return minimum;
}

pair<vector<double>,double> Clustering::Silhouette(){

	int sizeofClusters = this->clusters.size();

	int minCluster;

	vector<double> si;
	double s;
	double sum = 0.0;
	double sTotal = 0.0;

	for(int cluster1 =0; cluster1<sizeofClusters; cluster1++){

		vector<int> closestClusters;

		s = 0.0;

		vector<item*> itemsInCluster = clusters.at(cluster1)->getItems();
		int sizeofItemsInCluster = itemsInCluster.size();

		double min = numeric_limits<double>::max();
		for(int i=0; i < sizeofItemsInCluster; i++){

			for(int cluster2=0; cluster2 < sizeofClusters; cluster2++){
				if(cluster1 == cluster2)
					continue;

				double distance = dist(2,*(itemsInCluster.at(i)) , *(this->clusters.at(cluster2)->getCentroid()));
				if(distance < min){
					min = distance;
					minCluster = cluster2;
				}
			}
			closestClusters.push_back(minCluster);
		}
		
		double a = 0.0,b = 0.0;
		for(int i=0; i < sizeofItemsInCluster; i++){

			for(int j=0; j<sizeofItemsInCluster; j++){

				if(i == j)
					continue;

				a += dist(2,*(itemsInCluster.at(i)) , *(itemsInCluster.at(j)));
			}

			if(sizeofItemsInCluster <= 1)
				a = 0;
			else
				a = a/(sizeofItemsInCluster-1);

			vector<item*> itemsInClosestCluster = clusters.at(closestClusters.at(i))->getItems();
			
			int sizeofItemsInClosestCluster = itemsInClosestCluster.size();
			
			for (int k=0 ; k < sizeofItemsInClosestCluster ; k++)
				b += dist(2,*(itemsInCluster.at(i)) , *(itemsInClosestCluster.at(k)));
			
			if(sizeofItemsInClosestCluster <= 1)
				b = 0;
			else
				b = b/(sizeofItemsInClosestCluster-1);

			if(a < b) s = 1 - (a/b);
			else if(a == b) s = 0;
			else
				s = b/a -1;

			sum += s;

		}
		
		si.push_back(sum /sizeofItemsInCluster );
		sTotal += sum / sizeofItemsInCluster;
	}

	sTotal /= si.size();

	return make_pair(si,sTotal);
}

bool Clustering::exists(item* i){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		if( (*it)->exists(i) )
			return true;

	return false;	
}

// Cluster::Cluster(item* centroid){

// 	this->centroid = new item(*centroid);
// 	this->dimension = this->centroid->getDimension();
// 	this->items.push_back(centroid);
// }

// Cluster::~Cluster(){
// 	delete this->centroid;
// }

// item* Cluster::getCentroid(){
// 	return this->centroid;
// }

// void Cluster::insert(item* it){
// 	this->items.push_back(it);
// }

// int Cluster::print(){
// 	return this->items.size();
// }

// pair<string,vector<string>> Cluster::getCompleteCluster(){

// 	vector<string> ids;

// 	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
// 		ids.push_back((*it)->getID());

// 	return make_pair(this->centroid->getID(),ids);
// }

// bool Cluster::Update(){

// 	bool flag = false;

// 	double T = this->items.size();
// 	double sum = 0;

// 	vector<double> newCoordinates;

// 	// int dimension = this->dimension;

// 	for(int i=0; i<this->dimension; i++){
// 		// cout << "Got here" << endl;

// 		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
// 			sum += (*it)->getCoordinatein(i);
	
// 		double Mean = sum / T;

// 		// cout << "Got out" << endl;
// 		newCoordinates.push_back(Mean);

// 		sum = 0;

// 	}

// 	if(*(this->centroid->getVector()) == newCoordinates)
// 		flag = true;

// 	delete this->centroid;
// 	this->centroid = new item("newItem",newCoordinates);

// 	// cout << "New centroid is ";
// 	// this->centroid->print();cout << endl;

// 	// this->items.clear();

// 	// cout << "Returning" << endl;

// 	return flag;
// }

// void Cluster::clearCluster(){
// 	this->items.clear();
// }

// int Cluster::getDimension(){
// 	return this->dimension;
// }

// void Cluster::deleteItem(item *i){

// 	// cout << "Entered to delete " << i->getID() << endl;

// 	// cout << endl << "Items in cluster " << this->centroid->getID() << " are: ";
// 	// for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
// 	// 	cout << (*it)->getID() << " ";

// 	// cout << endl;

// 	vector<item*>::iterator toDelete = find(this->items.begin(),this->items.end(),i);
	
// 	// if(toDelete == this->items.end())
// 	// 	cout << "Not found" << endl;
// 	// else
// 	// 	cout << "Found" << endl;

// 	this->items.erase(toDelete);
// }

// bool Cluster::exists(item *i){

// 	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
// 		if((i->getID() == (*it)->getID()))
// 			return true;

// 	return false;
// }

// vector<item*> Cluster::getItems(){
// 	return this->items;
// }

// Clustering::Clustering(int K,int L,int kLSH,int M,int kCUBE,int probes,int w, int totalItems)
// : K(K), L(L), kLSH(kLSH), M(M), kCUBE(kCUBE), probes(probes), w(w), totalItems(totalItems) {}

// Clustering::~Clustering(){

// 	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
// 	delete *it; 
// }

// int Clustering::noItems(){
// 	return this->items.size();
// }

// void Clustering::insert(item* item){
// 	this->items.push_back(item);
// }

// vector<Cluster*> Clustering::getClusters(){
// 	return this->clusters;
// }

// pair<int,item*> Clustering::getClusterat(int index){

// 	Cluster *tmp = this->clusters.at(index);
// 	int size = tmp->getItems().size();
// 	item *centoid = tmp->getCentroid();

// 	return make_pair(size,centoid);
// }

// pair<string,vector<string>> Clustering::getCompleteClusterat(int index){
// 	return this->clusters.at(index)->getCompleteCluster();
// }


// void Clustering::kMeansPP(){

// 	int t =0;

// 	vector<item*> chosenCentroids;

// 	//vector<pair<item*,double> > array;

// 	item* firstCentroid = getRandomItem(this->items);

// 	chosenCentroids.push_back(firstCentroid);
// 	// deleteByValue(firstCentroid,&this->items);
// 	this->clusters.push_back(new Cluster(firstCentroid));

// 	t++;

// 	double minimum = numeric_limits<double>::max();
// 	item *minCentroid = NULL;

// 	vector<pair<double,item*>> P;

// 	while(t < this->K){

// 		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

// 			// for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

// 			// 	double distance = dist(2,**it,*(*it2)->getCentroid());

// 			// 	if( distance < minimum ){

// 			// 		minimum = distance;
// 			// 		minCentroid = (*it2)->getCentroid();
// 			// 	}
// 			// }

// 			// D.push_back(make_pair(*it,minimum));

// 			double sum =0;

// 			for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

// 				double distance = dist(2,**it,*(*it2)->getCentroid());
// 				distance = pow(distance,2);
				
// 				sum += distance;
// 			}

// 			P.push_back(make_pair(sum,*it));

// 		}

// 		sort(P.begin(),P.end());
// 		random_device rd;
// 		mt19937 gen(rd());
// 		uniform_real_distribution<> dis(0,P.at(P.size()-1).first);

// 		double temp = dis(gen);
// 		vector<pair<double,item*>>::iterator it3;
// 		for (it3 = P.begin() ; it3 != P.end() ; it3++){

// 			if ((*it3).first >= temp)
// 				break;

// 		}

// 		cout << "Inserting cluster " << (*it3).second->getID() << endl;
// 		this->clusters.push_back(new Cluster((*it3).second));

// 		t++;
// 	}
// }

// void Clustering::Assign(string assignMethod){

// 	Hash *h;
// 	// HyperCube* c;

// 	if(assignMethod == "LSH"){
	
// 		h = new Hash(this->kLSH, this->L, this->w, this->totalItems/4,this->clusters.at(0)->getDimension());
// 		// this->fillHash(h);
// 	}

// 	// if(assignMethod == "Hypercube"){

// 	// 	c = new HyperCube(this->kCUBE, this->w,this->M,this->probes,this->clusters.at(0)->getDimension());
// 	// 	this->fillCube(c);
// 	// }

// 	while(1){

// 		this->clearClusters();

// 		if(assignMethod == "Classic")
// 			this->Lloyd();
// 		else if(assignMethod == "LSH")
// 			this->LSH(h);
// 		else if(assignMethod == "Hypercube")
// 			this->Hypercube();	
// 		else{

// 			cerr << "Not valid assignment method given." << endl;
// 			return;
// 		}

// 		double temp = this->Update();
// 		cout << "It is " << temp << endl;

// 		if(temp == 1.0)
// 			break;
// 	}

// 	// delete h;
// 	// delete c;
// }

// void Clustering::Lloyd(){

// 	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

// 		double minimum = numeric_limits<double>::max();

// 		Cluster *minCluster;

// 		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

// 			int distance = dist(2,**it,*(*it2)->getCentroid());

// 			// cout << "Distance from " << ++count << " is " << distance << endl;

// 			// cout << "Item's " << (*it)->getID() << " distance from cluster " << count++ << " is " << distance << endl; 

// 			if( distance < minimum ){

// 				minimum = distance;
// 				minCluster = *it2;
// 			}
// 		}

// 		// cout << endl;

// 		minCluster->insert(*it);

// 	}
// }

// void Clustering::LSH(Hash *h){

// 	// cout << endl << "Starting LSH" << endl;

// 	double range = 197;//this->minDistCentroids()/2;
// 	// cout << "Range is " << range << endl;

// 	// Hash *h = new Hash(this->kLSH, this->L, this->w, this->totalItems/4,this->clusters.at(0)->getDimension());
// 	// this->fillHash(h);

// 	// cout << "Hash has a total of " << h->getItems().size() << endl;

// 	int totalItems = h->getItems().size();

// 	int pos = 0;

// 	int endCond = -1;
// 	int lastendCond = 0;
// 	// int totalItems = this->items.size();

// 	vector<pair<item*,double>> temp;

// 	while(endCond != lastendCond){

// 		lastendCond = endCond;
// 		endCond = 0;

// 		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

// 			// cout << "Calling findRange for " << (*it)->getCentroid()->getID() << endl;

// 			cout << "range is " << range << endl;
// 			temp = h->findRange(range,(*it)->getCentroid());

// 			cout << "Returned items: " << temp.size() << endl;

// 			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
				
// 				if( (*it2).first->getFlag() == -1 ){
					
// 					cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;

// 					(*it)->insert(it2->first);
// 					(*it2).first->setFlag(pos);
// 					endCond++;

// 				}else{

// 					item *newCentroid = (*it)->getCentroid();
// 					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

// 					double distanceNew = dist(2,*(*it2).first,*newCentroid);
// 					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

// 					// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;
// 					if( distanceNew < distanceOld ){

// 						cout << "Approved to add " << (*it2).first->getID() << " in cluster " << pos << " with flag " << (*it2).first->getFlag() << endl;
						
// 						(this->clusters.at((*it2).first->getFlag())->deleteItem((*it2).first));
// 						(*it)->insert(it2->first);
// 						(*it2).first->setFlag(pos);

// 						endCond++;
// 					}
// 				}
// 			}

// 			if( (long unsigned int)(++pos) == this->clusters.size())
// 				pos = 0;
			
// 		}

// 		range *= 2; 
// 		cout << "End cond is " << endCond << " while last end cond is " << lastendCond << endl;

// 	}

// 	this->assignRest(h->getItems());

// 	// delete h;
// }

// void Clustering::Hypercube(){

// 	double range = this->minDistCentroids()/2;
// 	// cout << "Range is " << range << endl;

// 	HyperCube *c = new HyperCube(this->kCUBE, this->w,this->M,this->probes,this->clusters.at(0)->getDimension());
// 	this->fillCube(c);

// 	// int totalItems = c->getItems().size();

// 	int pos = 0;

// 	int endCond = -1;
// 	int lastendCond = 0;
// 	// int totalItems = this->items.size();

// 	vector<pair<item*,double>> temp;

// 	while(endCond != lastendCond){

// 		// cout << "Range is " << range << endl;
// 		// cout << "Got here" << " with endCond " << endCond << endl;

// 		lastendCond = endCond;
// 		endCond = 0;

// 		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

// 			temp = c->findRange(range,(*it)->getCentroid(),this->M);

// 			// cout << "Returned items: " << temp.size() << endl;

// 			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
				
// 				// cout << "Entered here" << endl;

// 				if( (*it2).first->getFlag() == -1 ){
					
// 					// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;

// 					(*it)->insert(it2->first);
// 					(*it2).first->setFlag(pos);
// 					endCond++;

// 				}else{

// 					item *newCentroid = (*it)->getCentroid();
// 					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

// 					double distanceNew = dist(2,*(*it2).first,*newCentroid);
// 					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

// 					if( distanceNew < distanceOld ){

// 						// cout << "Inserting " << (*it2).first->getID() << " in cluster " << pos << endl;
						
// 						(this->clusters.at((*it2).first->getFlag())->deleteItem((*it2).first));
// 						(*it)->insert(it2->first);
// 						(*it2).first->setFlag(pos);

// 						endCond++;
// 					}
// 				}
// 			}

// 			if( (long unsigned int)(++pos) == this->clusters.size())
// 				pos = 0;
			
// 		}

// 		range *= 2; 
	
// 	}

// 	this->assignRest(c->getItems());

// 	delete c;

// }

// void Clustering::assignRest(vector<item*> items){

// 	for(vector<item*>::iterator it = items.begin(); it != items.end(); it++){

// 		// if((*it)->getFlag() != -1) continue;

// 		if(this->exists(*it)) continue;

// 		double minimum = numeric_limits<double>::max();

// 		Cluster *minCluster;

// 		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

// 			int distance = dist(2,**it,*(*it2)->getCentroid());

// 			// cout << "Distance from " << ++count << " is " << distance << endl;

// 			// cout << "Item's " << (*it)->getID() << " distance from cluster " << count++ << " is " << distance << endl; 

// 			if( distance < minimum ){

// 				minimum = distance;
// 				minCluster = *it2;
// 			}
// 		}

// 		// cout << endl;

// 		// cout << "Inserting item " << (*it)->getID() << " in cluster " << (*it)->getFlag() << endl;
// 		minCluster->insert(*it);
// 	}
// }

// double Clustering::Update(){

// 	double count = 0;

// 	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
// 		if((*it)->Update() == true)
// 			count++;

// 	// cout << "Syspro" << endl;
// 	// cout << "Size is " << this->clusters.size();

// 		cout << count << "/" << this->clusters.size() << endl;

// 	return (double)(count/this->clusters.size());	
// }

// void Clustering::clearClusters(){

// 	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
// 		(*it)->clearCluster();
// }

// void Clustering::print(){

// 	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
// 		cout << "Size: " << (*it)->print() << endl;
// }

// void Clustering::fillCube(HyperCube* cube){

// 	for (vector<item*>::iterator i = items.begin() ; i!=items.end() ; i++){

// 		(*i)->setFlag(-1);
// 		cube->insert(*i);
// 	}
// }

// void Clustering::fillHash(Hash* hash){

// 	for (vector<item*>::iterator i = items.begin() ; i!=items.end() ; i++){

// 		(*i)->setFlag(-1);
// 		hash->insert(*i);
// 	}
// }

// double Clustering::minDistCentroids(){
	
// 	double minimum = numeric_limits<double>::max();

// 	for(unsigned long int i=0; i < this->clusters.size(); i++)
// 		for(unsigned long int j=0; j < this->clusters.size(); j++){

// 			if( i == j ) continue;

// 			// cout << "Comparing centroid: ";
// 			// this->clusters.at(i)->getCentroid()->print();
// 			// cout << endl << " with centroid: ";
// 			// this->clusters.at(j)->getCentroid()->print();cout << endl;

// 			double distance = dist(2,*this->clusters.at(i)->getCentroid(),*this->clusters.at(j)->getCentroid());

// 			if(distance < minimum)
// 				minimum = distance;

// 		}

// 	return minimum;
// }

// pair<vector<double>,double> Clustering::Silhouette(){

// 	int sizeofClusters = this->clusters.size();

// 	vector<int> closestClusters;
// 	int minCluster;

// 	vector<double> si;
// 	double s;
// 	double sum = 0.0;
// 	double sTotal = 0.0;

// 	/* For every cluster */
// 	for (int cluster1 =0 ; cluster1<sizeofClusters ; cluster1++){

// 		s = 0.0;

// 		vector<item*> itemsInCluster = clusters.at(cluster1)->getItems();
// 		int sizeofItemsInCluster = itemsInCluster.size();

// 		/* Get every item's in cluster closest cluster. */
// 		double min = numeric_limits<double>::max();
// 		for(int i=0 ; i < sizeofItemsInCluster ; i++){

// 			for(int cluster2=0 ; cluster2 < sizeofClusters ; cluster2++){
				
// 				if(cluster1 == cluster2)
// 					continue;

// 				double distance = dist(2,*(itemsInCluster.at(i)) , *(this->clusters.at(cluster2)->getCentroid()));
// 				if(distance < min){
					
// 					min = distance;
// 					minCluster = cluster2;
// 				}
// 			}

// 			closestClusters.push_back(minCluster);
// 		}
		
// 		/* For every item in cluster again */
// 		double a = 0.0,b = 0.0;
// 		for(int i=0 ; i < sizeofItemsInCluster ; i++){

// 			/* Get total distance between items inside bucket */
// 			for(int j=0 ; j<sizeofItemsInCluster ; j++){

// 				if (i == j)
// 					continue;

// 				a += dist(2,*(itemsInCluster.at(i)) , *(itemsInCluster.at(j)));
// 			}

// 			if(sizeofItemsInCluster <= 1)
// 				a = 0;
// 			else
// 				a = a/(sizeofItemsInCluster-1);

// 			vector<item*> itemsInClosestCluster = clusters.at(closestClusters.at(i))->getItems();
			
// 			int sizeofItemsInClosestCluster = itemsInClosestCluster.size();
			
// 			/* And also total distance between items in closest bucket */
// 			for (int k=0 ; k < sizeofItemsInClosestCluster ; k++)
// 				b += dist(2,*(itemsInCluster.at(i)) , *(itemsInClosestCluster.at(k)));
			
// 			if(sizeofItemsInClosestCluster <= 1)
// 				b = 0;
// 			else
// 				b = b/(sizeofItemsInClosestCluster-1);

// 			if(a < b) s = 1 - (a/b);
// 			else if(a == b) s = 0;
// 			else
// 				s = b/a -1;

// 			sum += s;

// 		}
		
// 		si.push_back(sum /sizeofItemsInCluster );
// 		sTotal += sum / sizeofItemsInCluster;
// 	}

// 	sTotal /= si.size();

// 	return make_pair(si,sTotal);
// }

// bool Clustering::exists(item* i){

// 	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
// 		if( (*it)->exists(i) )
// 			return true;

// 	return false;	
// }