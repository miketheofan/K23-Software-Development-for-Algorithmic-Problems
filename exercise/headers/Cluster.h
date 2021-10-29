#ifndef CLUSTER_H
#define CLUSTER_H

using namespace std;

#include "./items.h"
#include "../headers/HyperCube.h"
#include "../headers/Hash.h"

class Cluster{

private:

	vector<item*> items;
	item* centroid;
	int dimension;

public:

	Cluster(item*);
	item* getCentroid();
	void insert(item*);
	bool Update();
	void clearCluster();
	int print();
	int getDimension();
	void deleteItem(item*);
	bool exists(item*);
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
	vector<item*> items;
	vector<Cluster*> clusters;

public:

	Clustering(int,int,int,int,int,int,int);
	int noItems();
	void insert(item*);
	void kMeansPP();
	void Assign(string);
	void Lloyd();
	// void Lloyd(vector<pair<item*,double>>);
	void LSH();
	void Hypercube();
	double Update();
	void clearClusters();
	void print();
	void fillCube(HyperCube*);
	void fillHash(Hash*);
	double minDistCentroids();
	void assignRest(vector<item*>);
	bool exists(item*);

};

#endif