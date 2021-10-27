#include "../headers/Cluster.h"
#include "../headers/utilCLUSTER.h"

Cluster::Cluster(item* centroid){

	this->centroid = centroid;
	this->items.push_back(this->centroid);
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

Clustering::Clustering(int K,int L,int kLSH,int M,int kCUBE,int probes)
: K(K), L(L), kLSH(kLSH), M(M), kCUBE(kCUBE), probes(probes){


}

void Clustering::insert(item* item){

	this->items.push_back(item);
}

void Clustering::kMeans(){

	int t =0;

	item* firstCentroid = getRandomItem(this->items);

	deleteByValue(firstCentroid,&this->items);
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

			if( pow((*it3).second,2)/probDividor > maximum ){

				maximum = (*it3).second;
				maximumItem = (*it3).first;
			}
		}

		deleteByValue(maximumItem,&this->items);
		this->clusters.push_back(new Cluster(maximumItem));

		t++;
	}
}

void Clustering::Assign(){

	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

		double minimum = numeric_limits<double>::max();

		Cluster *cluster;

		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			int distance = dist(2,**it,*(*it2)->getCentroid());

			if( distance < minimum ){

				minimum = distance;
				cluster = *it2;
			}
		}

		cluster->insert(*it);

		cluster->Update();
	}

}

void Clustering::print(){

	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		cout << "Size: " << (*it)->print() << endl;
}