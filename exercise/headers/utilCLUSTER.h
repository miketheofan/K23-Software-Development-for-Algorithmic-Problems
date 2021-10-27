#ifndef UTILCLUSTER_H
#define UTILCLUSTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

#include "./Cluster.h"

double dist(int,item,item);
void readConf(string,int *,int *,int *,int *,int *,int *);
void readDatasetCLUSTER(string,Clustering*);
item* getRandomItem(vector<item*>);
void deleteByValue(item*,vector<item*>*);
double prob(vector<pair<item*,double>>);

#endif