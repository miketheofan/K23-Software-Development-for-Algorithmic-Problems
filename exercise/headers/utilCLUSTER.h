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
// void deleteByValue(item*,vector<item*>*);
double prob(vector<pair<item*,double>>);
int32_t H(item *,int ,vector<double> * ,double );
vector<double>* produceNdistVector(int ,int ,int );
int module(int,int);
int32_t G(item*,int,int,vector<int32_t>,int,double,vector<double> *);

#endif