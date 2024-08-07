#ifndef CLUSTER_H
#define CLUSTER_H

#include <algorithm>

using namespace std;

#include "./items.h"
#include "../headers/HyperCube.h"
#include "../headers/Hash.h"
#include "../headers/DiscreteLSH.h"

class Cluster{

private:

	vector<item*> items;
	item* centroid;
	int dimension;

public:

	Cluster(item*);
	~Cluster();
	item* getCentroid();
	void insert(item*);
	bool Update();
	bool UpdateCurve();
	void clearCluster();
	int print();
	int getDimension();
	void deleteItem(item*);
	vector<item*> getItems();
	bool exists(item*);
	pair<string,vector<string>> getCompleteCluster();	
};

class Clustering{

private:

	int K;
	int L;
	int kLSH;
	int M;
	int kCUBE;
	int probes;
	int w;
	int totalItems;
	string update;
	string assignment;
	vector<item*> items;
	vector<curve*> curves;
	vector<Cluster*> clusters;

public:

	Clustering(int,int,int,int,int,int,int,int,string,string);
	~Clustering();
	int noItems();
	void insert(item*);
	vector<Cluster*> getClusters();
	void kMeansPP();
	void Assign(string);
	void Lloyd();
	pair<int,item*> getClusterat(int);
	pair<string,vector<string>> getCompleteClusterat(int);
	void LSH(Hash*);
	void Hypercube(HyperCube*);
	void lshFrechet(Discrete*);
	double Update();
	void clearClusters();
	void print();
	void fillCube(HyperCube*);
	void fillHash(Hash*);
	void fillDiscrete(Discrete*);
	double minDistCentroids();
	double minDistCentroidsCurve();
	void assignRest(vector<item*>);
	bool exists(item*);
	pair<vector<double>,double> Silhouette();

};

#endif