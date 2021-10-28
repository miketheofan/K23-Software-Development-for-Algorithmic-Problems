#ifndef CLUSTER_H
#define CLUSTER_H

using namespace std;

#include "./items.h"

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
	int print();
};

class Clustering{

private:

	int K;
	int L;
	int kLSH;
	int M;
	int kCUBE;
	int probes;
	vector<item*> items;
	vector<Cluster*> clusters;

public:

	Clustering(int,int,int,int,int,int);
	int noItems();
	void insert(item*);
	void kMeansPP();
	void Assign();
	double Update();
	void print();

};

#endif