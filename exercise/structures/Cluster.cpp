#include "../headers/Cluster.h"
#include "../headers/utilCLUSTER.h"

Cluster::Cluster(item* centroid){

	this->centroid = centroid;
	this->dimension = this->centroid->getDimension();
	this->items.push_back(new item(*centroid));
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

	this->items.clear();

	// cout << "Returning" << endl;

	return flag;
}

Clustering::Clustering(int K,int L,int kLSH,int M,int kCUBE,int probes)
: K(K), L(L), kLSH(kLSH), M(M), kCUBE(kCUBE), probes(probes){


}

int Clustering::noItems(){
	return this->items.size();
}

void Clustering::insert(item* item){
	this->items.push_back(item);
}

void Clustering::kMeansPP(){

	int t =0;

	vector<item*> chosenCentroids;

	item* firstCentroid = getRandomItem(this->items);

	chosenCentroids.push_back(firstCentroid);
	// deleteByValue(firstCentroid,&this->items);
	this->clusters.push_back(new Cluster(firstCentroid));

	t++;

	double minimum = numeric_limits<double>::max();
	item *minCentroid = NULL;

	vector<pair<item*,double>> D;

	while(t < this->K){

		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

			for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

				double distance = dist(2,**it,*(*it2)->getCentroid());

				if( distance < minimum ){

					minimum = distance;
					minCentroid = (*it2)->getCentroid();
				}
			}

			D.push_back(make_pair(*it,minimum));
		}

		double maximum = numeric_limits<double>::min();
		item *maximumItem = NULL;

		double probDividor = prob(D);

		for(vector<pair<item*,double>>::iterator it3 = D.begin(); it3 != D.end(); it3++){

			if(find(chosenCentroids.begin(),chosenCentroids.end(), (*it3).first) != chosenCentroids.end())
				continue;

			if( pow((*it3).second,2)/probDividor > maximum ){

				maximum = (*it3).second;
				maximumItem = (*it3).first;
			}
		}
 
		// deleteByValue(maximumItem,&this->items);
		chosenCentroids.push_back(maximumItem);
		this->clusters.push_back(new Cluster(maximumItem));

		t++;
	}
}

void Clustering::Assign(){

	int count = 0;

	while(1){

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

			count =0;
		}

		cout << "Before update ||" << endl;
		this->print();

		if(this->Update() == 1.0)
			break;

		cout << "After update ||" << endl;
		this->print();
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

void Clustering::print(){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		cout << "Size: " << (*it)->print() << endl;
}