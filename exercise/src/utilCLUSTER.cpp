#include "../headers/utilCLUSTER.h"

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

void readConf(string fileName,int *K,int *L,int *kLSH,int *M,int *kCUBE,int *probes){

	ifstream fp;
	fp.open(fileName);

	string line, word;
	int target =0;

	while( getline(fp,line) ){

		stringstream linestream(line);
		int counter =0;

		while(linestream >> word){

			if(!counter++)
				continue;

			switch(target++){

				case(0):{

					*K = stoi(word);
					break;
				}case(1):{

					*L = stoi(word);
					break;
				}case(2):{

					*kLSH = stoi(word);
					break;
				}case(3):{

					*M = stoi(word);
					break;
				}case(4):{

					*kCUBE = stoi(word);
					break;
				}case(5):{

					*probes = stoi(word);
					break;
				}
			}
		}
	}
}

void readDatasetCLUSTER(string fileName,Clustering* cluster){

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

		cluster->insert(new item(id,words));
		// item temp(id,words);
		// temp.print();
	}
}

item* getRandomItem(vector<item*> i){

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,i.size());

	return i.at(distance(generator));
}

// void deleteByValue(item* i,vector<item*> *items){

// 	for(unsigned long int j=0;j<items->size();j++)
// 		if(items->at(j)->getID() == i->getID())
// 	    	items->erase(items->at(j));
// 	else
// 		cout << "GOt here\n";
// }

double prob(vector<pair<item*,double>> D){

	double add = 0;

	for(vector<pair<item*,double>>::iterator it = D.begin(); it != D.end(); it++)
		add += pow((*it).second,2);

	return add;
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