#ifndef H_H
#define H_H

#include <iostream>
#include <algorithm>

using namespace std;

#include "./items.h"

class Hi{

private:

	double t;
	int w;
	vector<double> *v;

public:

	Hi(int,int);
	~Hi();
	int32_t Hashi(item*);

};

#endif