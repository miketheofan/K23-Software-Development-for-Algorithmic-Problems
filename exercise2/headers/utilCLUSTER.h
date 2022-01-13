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
#include "./DiscreteLSH.h"
#include "./ContinuousLSH.h"

double dist(int,item,item);
double distFrechet(item*,item*);
vector<vector<double>> distFrechetMean(curve*,curve*);
double distFrechet(curve*,item*);
double distFrechet(curve*,curve*);
double distFrechetBrute(curve*,curve*);
void readConf(string,int *,int *,int *,int *,int *,int *);
void readDatasetCLUSTER(string,Clustering*,vector<item*>*);
item* getRandomItem(vector<item*>);
vector<double>* produceNdistVector(int ,int ,int );
int module(int,int);
int getDimension(string);
void writeToFile(string,string);
void functionality(string,string,int,int,int,int,int,int,int,bool,int,string,string);
void fillDatasetCLUSTER(vector<item*>,Clustering*);
int countItems(string);
curve* Polygonization(item*);
vector<double> MeanCurve(vector<double>,vector<double>);

#endif