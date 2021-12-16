#include "../headers/Cluster.h"
#include "../headers/utilCLUSTER.h"

Cluster::Cluster(item* centroid){

	/* First we store item given as this current cluster's centroid. */
	this->centroid = new item(*centroid);
	this->dimension = this->centroid->getDimension();
	
	/* We also insert the centroid in the item's vector. That is because the 'random' centroid with 
	which every cluster will be initialized will be replaced later with random ones so we must not lose
	him from the items vector. */
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

/* Following function is used to return a pair that contains <cetroid of cluster,list of items in cluster>. */
pair<string,vector<string>> Cluster::getCompleteCluster(){

	vector<string> ids;

	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
		ids.push_back((*it)->getID());

	return make_pair(this->centroid->getID(),ids);
}

/* The following is our implementation of the Update function. */
bool Cluster::Update(){

	bool flag = false;

	double T = this->items.size();
	double sum = 0;

	vector<double> newCoordinates;

	/* For every coordinate of each item in cluster */
	for(int i=0; i<this->dimension; i++){

		/* We get its value */
		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++)
			sum += (*it)->getCoordinatein(i);
	
		/* And calculate the mean. */
		double Mean = sum / T;

		newCoordinates.push_back(Mean);

		sum = 0;

	}

	/* If centroid did not change raise a flag. */
	if(*(this->centroid->getVector()) == newCoordinates)
		flag = true;

	/* Delete previous centroid(that is why we needed to insert first centroid in items vector because otherwise
	we would lose it). */
	delete this->centroid;
	/* And create a new centroid for this cluster. */
	this->centroid = new item("newItem",newCoordinates);

	return flag;
}

void Cluster::clearCluster(){
	this->items.clear();
}

int Cluster::getDimension(){
	return this->dimension;
}

/* The following function is used in order to delete an item from a certain cluster because it needs to be inserted
to another cluster. */
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
: K(K), L(L), kLSH(kLSH), M(M), kCUBE(kCUBE), probes(probes), w(w), totalItems(totalItems) {}

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

/* The following function is our implementation for the k-means++ algorithm. */
void Clustering::kMeansPP(){

	int t =0;

	vector<item*> chosenCentroids;

	/* First we initialize out first centroid with a random item in items vector. */
	item* firstCentroid = getRandomItem(this->items);

	chosenCentroids.push_back(firstCentroid);
	this->clusters.push_back(new Cluster(firstCentroid));

	t++;

	vector<pair<double,item*>> P;

	/* As long as we haven't initialized K centroids. */
	while(t < this->K){

		/* Iterate through all items. */
		for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

			double sum =0;

			/* And for every item calculate its distance from all centroids. */
			for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

				double distance = dist(2,**it,*(*it2)->getCentroid());
				distance = pow(distance,2);
				
				sum += distance;
			}

			P.push_back(make_pair(sum,*it));

		}

		/* Sort the distance array. */
		sort(P.begin(),P.end());
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(0,P.at(P.size()-1).first);

		double temp = dis(gen);

		vector<pair<double,item*>>::iterator it3;
		/* And choose uniformly the item that will be used for the new cluster. */
		for(it3 = P.begin() ; it3 != P.end() ; it3++)
			if((*it3).first >= temp) break;

		/* Initialize a new cluster with the centroid that we just computed. */
		this->clusters.push_back(new Cluster((*it3).second));

		t++;
	}
}

/* The following function is our implementation for the Assign function. */
void Clustering::Assign(string assignMethod){

	Hash *h;
	HyperCube *c;
	Continuous *cont;

	/* If assign method is LSH then fill a Hash structure using the items vector. */
	if(assignMethod == "LSH"){

		h = new Hash(this->kLSH, this->L, this->w, this->totalItems/4,this->clusters.at(0)->getDimension());
		this->fillHash(h);
	}

	/* If assign method is Hypercube then fill a HyperCube structure using the items vector. */
	if(assignMethod == "Hypercube"){

		c = new HyperCube(this->kCUBE, this->w,this->M,this->probes,this->clusters.at(0)->getDimension());
		this->fillCube(c);
	}

	if(assignMethod == "LSH_Frechet"){

		cont = new Continuous(this->kLSH,this->w,this->L,this->totalItems/4,this->clusters.at(0)->getDimension(),2.5,"continuous");
		this->fillContinuous(cont);
	}

	while(1){

		/* Every time clear all clusters, because we will re-fill them using the corresponding Update function. */
		this->clearClusters();

		if(assignMethod == "Classic")
			this->Lloyd();
		else if(assignMethod == "LSH")
			this->LSH(h);
		else if(assignMethod == "Hypercube")
			this->Hypercube(c);	
		else if(assignMethod == "LSH_Frechet")
			this->lshFrechet(cont);
		else{

			cerr << "Not valid assignment method given." << endl;
			return;
		}

		/* If exit case was fulfilled then Assignment is complete. */
		if(this->Update() == 1)
			break;

	}

	if(assignMethod == "LSH") delete h;
	if(assignMethod == "Hypercube") delete c;
	if(assignMethod == "LSH_Frechet") delete cont;
}

/* The following function is our implementation for the Lloyd algorithm. */
void Clustering::Lloyd(){

	/* For every item in items vector */
	for(vector<item*>::iterator it = this->items.begin(); it != this->items.end(); it++){

		double minimum = numeric_limits<double>::max();

		Cluster *minCluster;

		/* Get the closest cluster to this certain item. */
		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			int distance = dist(2,**it,*(*it2)->getCentroid());

			if( distance < minimum ){

				minimum = distance;
				minCluster = *it2;
			}
		}

		/* And then insert the item in the closest cluster. */
		minCluster->insert(*it);

	}
}

/* The following function is our implementation for reverse assignment algorithm using LSH. */
void Clustering::LSH(Hash *h){

	/* Range is initialized with value similar to the minimum distance between centroids divided by 2. */
	double range = this->minDistCentroids()/2;

	int totalItems = h->getItems().size();

	int pos = 0;

	int endCond = -1;
	int lastendCond = 0;

	vector<pair<item*,double>> temp;

	/* Our implementation ends when by multiplying the range, not any more item was assigned to a cluster, compared to the
	previous loop. */
	while(endCond != lastendCond){

		lastendCond = endCond;
		endCond = 0;

		/* For every cluster */
		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

			/* use the range search function of LSH in order to find items in range 'range'. */
			temp = h->findRange(range,(*it)->getCentroid());

			/* For every item that was returned by range search */
			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
								
				/* If they haven't been assigned to a cluster yet */
				if( (*it2).first->getFlag() == -1 ){
					
					/* Insert it to cluster */
					(*it)->insert(it2->first);
					/* and set its flag accoridingly, in order for later loops to know that item is already assigned. */
					(*it2).first->setFlag(pos);
					endCond++;

				/* Otherwise, if item is already assigned, then compare the distance of the cluster that it is already assigned
				with the distance to this current cluster. */
				}else{

					item *newCentroid = (*it)->getCentroid();
					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

					double distanceNew = dist(2,*(*it2).first,*newCentroid);
					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

					/* If item is closer to current cluster, insert it. */
					if( distanceNew < distanceOld ){
						
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

		/* Multiply range by 2 for next loop. */
		range *= 2; 
	
	}

	/* For any items that were not inserted using range search, insert them using Lloyd's algorithm(manually). */
	this->assignRest(h->getItems());

}

/* The following function is our implementation for reverse assignment algorithm using Hypercube. */
void Clustering::Hypercube(HyperCube *c){

	/* Range is initialized with value similar to the minimum distance between centroids divided by 2. */
	double range = this->minDistCentroids()/2;

	int pos = 0;

	int endCond = -1;
	int lastendCond = 0;

	vector<pair<item*,double>> temp;

	/* Our implementation ends when by multiplying the range, not any more item was assigned to a cluster, compared to the
	previous loop. */
	while(endCond != lastendCond){

		lastendCond = endCond;
		endCond = 0;

		/* For every cluster */
		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

			/* use the range search function of Hypercube in order to find items in range 'range'. */
			temp = c->findRange(range,(*it)->getCentroid(),this->M);

			/* For every item that was returned by range search */
			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
				
				/* If they haven't been assigned to a cluster yet */
				if( (*it2).first->getFlag() == -1 ){
					
					/* Insert it to cluster */
					(*it)->insert(it2->first);
					/* and set its flag accoridingly, in order for later loops to know that item is already assigned. */
					(*it2).first->setFlag(pos);
					endCond++;

				/* Otherwise, if item is already assigned, then compare the distance of the cluster that it is already assigned
				with the distance to this current cluster. */
				}else{

					item *newCentroid = (*it)->getCentroid();
					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

					double distanceNew = dist(2,*(*it2).first,*newCentroid);
					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

					/* If item is closer to current cluster, insert it. */
					if( distanceNew < distanceOld ){
						
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

		/* Multiply range by 2 for next loop. */
		range *= 2; 
	
	}

	/* For any items that were not inserted using range search, insert them using Lloyd's algorithm(manually). */
	this->assignRest(c->getItems());

}

void Clustering::lshFrechet(Continuous* cont){

	/* Range is initialized with value similar to the minimum distance between centroids divided by 2. */
	double range = this->minDistCentroids()/2;

	int pos = 0;

	int endCond = -1;
	int lastendCond = 0;

	vector<pair<item*,double>> temp;

	/* Our implementation ends when by multiplying the range, not any more item was assigned to a cluster, compared to the
	previous loop. */
	while(endCond != lastendCond){

		lastendCond = endCond;
		endCond = 0;

		/* For every cluster */
		for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++){

			/* use the range search function of Hypercube in order to find items in range 'range'. */
			temp = cont->rangeSearch(range,(*it)->getCentroid());

			/* For every item that was returned by range search */
			for(vector<pair<item*,double> >::iterator it2 = temp.begin(); it2 != temp.end(); it2++ ){
				
				/* If they haven't been assigned to a cluster yet */
				if( (*it2).first->getFlag() == -1 ){
					
					/* Insert it to cluster */
					(*it)->insert(it2->first);
					/* and set its flag accoridingly, in order for later loops to know that item is already assigned. */
					(*it2).first->setFlag(pos);
					endCond++;

				/* Otherwise, if item is already assigned, then compare the distance of the cluster that it is already assigned
				with the distance to this current cluster. */
				}else{

					item *newCentroid = (*it)->getCentroid();
					item *oldCentroid = this->clusters.at((*it2).first->getFlag())->getCentroid();

					double distanceNew = dist(2,*(*it2).first,*newCentroid);
					double distanceOld = dist(2,*(*it2).first,*oldCentroid);

					/* If item is closer to current cluster, insert it. */
					if( distanceNew < distanceOld ){
						
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

		/* Multiply range by 2 for next loop. */
		range *= 2; 
	
	}

	/* For any items that were not inserted using range search, insert them using Lloyd's algorithm(manually). */
	this->assignRest(cont->getItems());
}

/* The following function is used by reverse assignment to manually insert the remaining items in closest clusters. */
void Clustering::assignRest(vector<item*> items){

	/* For every item in items vector. */
	for(vector<item*>::iterator it = items.begin(); it != items.end(); it++){

		/* If item is already assigned to any cluster */
		if(this->exists(*it)) continue;

		double minimum = numeric_limits<double>::max();

		Cluster *minCluster;

		/* Find the closest cluster and insert it. */
		for(vector<Cluster*>::iterator it2 = this->clusters.begin(); it2 != this->clusters.end(); it2++){

			int distance = dist(2,**it,*(*it2)->getCentroid());

			if( distance < minimum ){

				minimum = distance;
				minCluster = *it2;
			}
		}

		minCluster->insert(*it);
	}
}

/* The following function is our implementation for the Update function. */
double Clustering::Update(){

	double count = 0;

	/* For every cluster, compute the Mean, update the centroid and return how many centroids remained the same. */
	for(vector<Cluster*>::iterator it = this->clusters.begin(); it != this->clusters.end(); it++)
		if((*it)->Update() == true)
			count++;

	/* Finally return the percentage of clusters that stayed the same. */
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

void Clustering::fillContinuous(Continuous* cont){

	for(vector<item*>::iterator i = items.begin(); i!=items.end(); i++)
		cont->insert(*i);
}


/* The following function computes the minimum distance between any centroid of Clustering structure. */
double Clustering::minDistCentroids(){
	
	double minimum = numeric_limits<double>::max();

	for(unsigned long int i=0; i < this->clusters.size(); i++)
		for(unsigned long int j=0; j < this->clusters.size(); j++){

			if( i == j ) continue;

			double distance = dist(2,*this->clusters.at(i)->getCentroid(),*this->clusters.at(j)->getCentroid());

			if(distance < minimum)
				minimum = distance;

		}

	return minimum;
}

/* The following function is our implementation for the Silhouette function. */
pair<vector<double>,double> Clustering::Silhouette(){

	int sizeofClusters = this->clusters.size();

	int minCluster;

	vector<double> si;
	double s;
	double sum = 0.0;
	double sTotal = 0.0;

	/* For every cluster */
	for(int cluster1 =0; cluster1<sizeofClusters; cluster1++){

		vector<int> closestClusters;

		s = 0.0;

		vector<item*> itemsInCluster = clusters.at(cluster1)->getItems();
		int sizeofItemsInCluster = itemsInCluster.size();

		/* for every item in cluster */
		double min = numeric_limits<double>::max();
		for(int i=0; i < sizeofItemsInCluster; i++){

			/* Find the second closest cluster. */
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
		/* For every item again */
		for(int i=0; i < sizeofItemsInCluster; i++){

			/* compute a according to the paper */
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
			
			/* compute b according to the paper */
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