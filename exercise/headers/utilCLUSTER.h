#ifndef UTILCLUSTER_H
#define UTILCLUSTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "./Cluster.h"

double dist(int,item,item);
void readConf(string,int *,int *,int *,int *,int *,int *);
void readDatasetCLUSTER(string,Clustering*,vector<item*>*);
item* getRandomItem(vector<item*>);
double prob(vector<pair<item*,double>>);
int32_t H(item *,int ,vector<double> * ,double );
vector<double>* produceNdistVector(int ,int ,int );
int module(int,int);
int32_t G(item*,int,int,vector<int32_t>,int,double,vector<double> *);
int calculateW(string,int);
int getDimension(string);
void writeToFile(string,string);
void functionality(string,string,int,int,int,int,int,int,int,bool);
void fillDatasetCLUSTER(vector<item*>,Clustering*);

#endif