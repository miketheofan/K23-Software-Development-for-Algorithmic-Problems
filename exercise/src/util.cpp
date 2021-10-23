#include "../headers/util.h"

double dist(item x,item y){

	if(x.getVector()->size() != y.getVector()->size()){

		cerr << "Cannot compute Euclidean Distance between vertexes from different dimensions." << endl;
		return 0;
	}

	unsigned long int d = x.getVector()->size();
	double result = 0.0;

	for(unsigned long int i = 0;i<d;i++)
		result += pow((*x.getVector()).at(i)-(*y.getVector()).at(i),2);
	
	return sqrt(result);
}

int module(int a, int b){
    return (a%b + b) % b;
}

void readDataset(string fileName,Hash* hash){

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

		hash->insert(new item(id,words));
		// item temp(id,words);
		// temp.print();
	}
}

int countItems(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line;
	int n =0;

	while( getline(fp,line) )
		n++;

	return n;

}

vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(/*mean=*/mean, /*standard deviation=*/stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}

int32_t H(item *p,int w){

	// p->print();

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,w);

	double t = distance(generator);
	// cout << "t is " << t << endl;

	/* We use normal distribution in order to generate a random vector v. */
	vector<double> *v = produceNdistVector(p->getDimension(),0.0,1.0);

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

int32_t G(item* p,int w,int k,int tableSize){

    srand(time(0));
    uint32_t M = pow(2,32)-5;

	// vector<uint32_t> hashFunctions;
	int32_t result =0;

	for(int i=0;i<k;i++){

		int32_t r = rand();

		// cout << "Before addition is: " << (result) << endl;
		result += H(p,w)*r;
		// cout << "After addition is: " << (result) << endl;
	}

	// cout << "It came out as: " << result << endl;

	result = module(result,M);

	// cout << endl << "NOw IT IS " << result << endl;

	// result2 = module(result,M);
	result = module(result,tableSize);
	// result2 = module(result,tableSize);
	
	// cout << "Result is: " << result << endl;

	return result;

}

void answerQueries(Hash hash,string fileName){

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

		item queryItem(id,words);

		// cout << "Item " << id << " has nearest-neighbour " << hash.findNN(&queryItem)->getID() << endl;
	
		vector<pair<double,item*>> results = hash.findkNN(5,&queryItem);

		cout << "Item " << id << " 5 closest neighbours: " << endl;
		for(unsigned long int i=0;i<results.size();i++){

			if(results.at(i).second != NULL)
				cout << results.at(i).first << " , " << results.at(i).second->getID() << endl;
		}
		cout << endl;
	}
}