#include "../headers/G.h"
#include "../headers/utilLSH.h"

Gi::Gi(int k,int dimension,int w) : k(k) , w(w) {

	srand(time(NULL));

	for(int i=0;i<this->k;i++)
		this->rVector.push_back((int32_t)rand());

	for(int i=0;i<this->k;i++)
		this->hVector.push_back(new Hi(dimension,w));
}

Gi::~Gi(){

	for(vector<Hi*>::iterator it = this->hVector.begin(); it != this->hVector.end(); it++)
		delete (*it);
}

int32_t Gi::Hashi(item *p,int tableSize){

	long int M = pow(2,32/k);
    // cout << "M : " << M << endl;

	// vector<uint32_t> hashFunctions;
	int result =0;
	//int32_t temp;
	for(int i=0;i<k;i++){

		// int32_t r = rand();

		// cout << "Before addition is: " << (result) << endl;
		//temp = H(p,w);
		//temp = module(temp,M);
		// cout << "temp is : " << temp << endl;
		int temp = module(this->hVector.at(i)->Hashi(p)*this->rVector.at(i),M);
		// cout << "Result is " << temp << endl;
		result += temp;
		// cout << "After addition is: " << (result) << endl;
	}

	// cout << "It came out as: " << result << endl;
	//cout << "Result is : " << result;
	result = module(result,M);
	// cout << "After modM is " << result << endl;
	p->setTrick(result);
	// cout << endl << "NOw IT IS " << result << endl;

	// result2 = module(result,M);
	result = module(result,tableSize);
	// cout << "After mod" << tableSize << " is " << result << endl;
	// result2 = module(result,tableSize);
	
	//cout << "Result is: " << result << endl;
	return result;
}