#ifndef CLUSTER_H
#define CLUSTER_H

using namespace std;

#include "./items.h"

class Cluster{

private:

	vector<item*> items;
	item* centroid;

public:

	Cluster(item*);
	item* getCentroid();
	void insert(item*);
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
	void insert(item*);
	void kMeans();
	void Assign();
	void print();

};

#endif