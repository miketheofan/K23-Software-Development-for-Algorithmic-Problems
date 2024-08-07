#ifndef G_H
#define G_H

#include <iostream>
#include <cmath>

using namespace std;

#include "./H.h"
#include "./items.h"

class Gi{

private:

	int k;
	int w;
	vector<Hi*> hVector;
	vector<int32_t> rVector;

public:

	Gi(int,int,int);
	~Gi();
	int32_t Hashi(item*,int);
 
};

#endif