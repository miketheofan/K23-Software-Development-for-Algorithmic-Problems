#include "../headers/util.h"

double dist(item x,item y){

	if(x.getVector().size() != y.getVector().size()){

		cerr << "Cannot compute Euclidean Distance between vertexes from different dimensions." << endl;
		return 0;
	}

	unsigned long int d = x.getVector().size();
	double result = 0.0;

	for(unsigned long int i = 0;i<d;i++)
		result += pow(x.getVector()[i]-y.getVector()[i],2);
	
	return sqrt(result);
}