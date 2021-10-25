#include "../headers/utilCUBE.h"

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

vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(/*mean=*/mean, /*standard deviation=*/stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}