#include "../headers/utilCUBE.h"

/* Distance calculator function is implemented in order to be easily extendable in vector 
spaced with other metrics. */
double dist(int distance,item x,item y){

	if(x.getVector()->size() != y.getVector()->size()){

		cerr << "Cannot compute Euclidean Distance between vertexes from different dimensions." << endl;
		return 0;
	}

	unsigned long int d = x.getVector()->size();
	double result = 0.0;

	for(unsigned long int i = 0;i<d;i++)
		result += pow((*x.getVector()).at(i)-(*y.getVector()).at(i),distance);
	
	return pow(result,1.0/distance);
}

void readDatasetCUBE(string fileName,HyperCube* cube){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		cube->insert(new item(id,words));
		// item temp(id,words);
		// temp.print();
	}
}

int32_t H(item *p,int w,vector<double> * v,double t){

	// p->print();

	// /* We use uniform distribution in order to generate a random t in range [0,w). */
	// random_device rd;
	// mt19937 generator(rd());
	// uniform_real_distribution<> distance(0,w);

	// double t = distance(generator);
	// cout << "t is " << t << endl;

	/* We use normal distribution in order to generate a random vector v. */
	// vector<double> *v = produceNdistVector(p->getDimension(),0.0,1.0);

	// cout << "v ";
	// for(unsigned long int i=0;i<v->size();i++)
	// 	cout << (*v)[i] << " "; 
	// cout << endl;

	/* We calculate the scaler product between vectors p and (randomly generated) v. */
	double scalerProduct = inner_product(p->getVector()->begin(),p->getVector()->end(),v->begin(),0.0);

	// double scalerProduct = 0.0;

	// cout << "Scaler product is " << scalerProduct << endl;

	return (int32_t)floor( (scalerProduct + t) / (double)w );

}

vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(/*mean=*/mean, /*standard deviation=*/stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}

void answerQueries(HyperCube cube,string inputFile,string queryFile,int M,int N,int R){

	ifstream fp;
	fp.open(queryFile);

	string line,id,word;
	int counter =0;

	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		item queryItem(id,words);

		pair<item*,double> query = cube.findNN(&queryItem,M);

		cout << "Query: " << queryItem.getID() << endl;
		cout << "Nearest neighbor-1: " << query.first->getID() << endl;
		cout << "distanceLSH: " << query.second << endl;
		cout << "distanceTrue: " << bruteNN(&queryItem,inputFile) << endl;

		vector<pair<double,item*>> tempVector = cube.findkNN(&queryItem,M,N);
		
		auto startLSH = high_resolution_clock::now();

		cout << "Nearest neigbor-" << N << ":";
		if(tempVector.size() == (unsigned long int)N)		
			cout << tempVector.at(N-1).second->getID();
		cout << endl;

		cout << "distanceLSH: ";
		if(tempVector.size() == (unsigned long int)N)		
			cout << tempVector.at(N-1).first;
		cout << endl;

		auto endLSH = high_resolution_clock::now();

		auto startTrue = high_resolution_clock::now();

		cout << "distanceTrue: ";
		if(tempVector.size() == (unsigned long int)N)		
			cout << brutekNN(N,&queryItem,inputFile);
		cout << endl;

		auto endTrue = high_resolution_clock::now();

		cout << "tLSH: " << (double)duration_cast<milliseconds>(endLSH - startLSH).count() << endl;
		cout << "tTrue: " << (double)duration_cast<milliseconds>(endTrue - startTrue).count() << endl;
		cout << R << "-near neigbors: " << endl;
		vector<pair<item*,double>> results = cube.findRange(R,&queryItem,M);
		for(unsigned long int i=0;i<results.size();i++)
			if(results.at(i).first != NULL)
				cout << results.at(i).first->getID() << endl;

		cout << endl;
	}
}