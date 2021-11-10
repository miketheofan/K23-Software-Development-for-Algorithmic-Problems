#include "../headers/utilLSH.h"

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

int module(int a, int b){
    return (a%b + b) % b;
}

void readDatasetLSH(string fileName,Hash* hash,vector<item*> *dataset){

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

		item* newItem = new item(id,words);
		dataset->push_back(newItem);

		hash->insert(newItem);
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

// int32_t H(item *p,int w,double t,vector<double> *v){

// 	/* We calculate the scaler product between vectors p and (randomly generated) v. */
// 	double scalerProduct = inner_product(p->getVector()->begin(),p->getVector()->end(),v->begin(),0.0);

// 	return (int32_t)floor( (scalerProduct + t) / (double)w );

// }

// int32_t G(item* p,int w,int k,vector<int32_t> rVector,int tableSize/*,double t,vector<double> *v*/){

// 	/* We use uniform distribution in order to generate a random t in range [0,w). */
// 	random_device rd;
// 	mt19937 generator(rd());
// 	uniform_real_distribution<> distance(0,w);

// 	double t = distance(generator);

// 	/* We use normal distribution in order to generate a random vector v. */
// 	vector<double> *v = produceNdistVector(p->getDimension(),0.0,1.0);

//     long int M = pow(2,32/k);
//     // cout << "M : " << M << endl;

// 	// vector<uint32_t> hashFunctions;
// 	int result =0;
// 	//int32_t temp;
// 	for(int i=0;i<k;i++){

// 		// int32_t r = rand();

// 		// cout << "Before addition is: " << (result) << endl;
// 		//temp = H(p,w);
// 		//temp = module(temp,M);
// 		// cout << "temp is : " << temp << endl;
// 		int temp = module(H(p,w,t,v)*rVector.at(i),M);
// 		// cout << "Result is " << temp << endl;
// 		result += temp;
// 		// cout << "After addition is: " << (result) << endl;
// 	}

// 	// cout << "It came out as: " << result << endl;
// 	//cout << "Result is : " << result;
// 	result = module(result,M);
// 	// cout << "After modM is " << result << endl;
// 	p->setTrick(result);
// 	// cout << endl << "NOw IT IS " << result << endl;

// 	// result2 = module(result,M);
// 	result = module(result,tableSize);
// 	// cout << "After mod" << tableSize << " is " << result << endl;
// 	// result2 = module(result,tableSize);
	
// 	//cout << "Result is: " << result << endl;

// 	delete v;
// 	return result;

// }

void answerQueries(Hash *hash,string fileName,string dataFile,int N,int R,string outputFile){

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

		writeToFile(outputFile,"Query: " + queryItem.getID() + "\n");
		// cout << "Query: " << queryItem.getID() << endl;

		item* nearestNeghbor = hash->findNN(&queryItem).first;

		if(nearestNeghbor != NULL){
			
			writeToFile(outputFile,"Nearest neighbor-1: " + nearestNeghbor->getID() + "\n");
			// cout << "Nearest neighbor-1: " << nearestNeghbor->getID() << endl;		
			writeToFile(outputFile,"distanceLSH: " + to_string(hash->findNN(&queryItem).second) + "\n");
			// cout << "distanceLSH: " << cube->findNN(&queryItem,M).second << endl;
			writeToFile(outputFile,"distanceTrue: " + to_string(bruteNN(&queryItem,dataFile)) + "\n");
			// cout << "distanceTrue: " << bruteNN(&queryItem,dataFile) << endl;
		}else{

			writeToFile(outputFile,"Nearest neighbor-1: NULL\n");
			// cout << "Nearest neighbor-1: NULL" << endl;
			writeToFile(outputFile,"distanceLSH: NULL\n");
			// cout << "distanceHypercube: NULL" << endl;
			writeToFile(outputFile,"distanceTrue: " + to_string(bruteNN(&queryItem,dataFile)) + "\n");
			// cout << "distanceTrue: " << bruteNN(&queryItem,dataFile) << endl;
		}

		vector<pair<double,item*>> tempVector = hash->findkNN(N,&queryItem);

		double totalHypercube =0;
		double totalTrue =0;

		auto startHypercube = high_resolution_clock::now();

		for(int i=2;i<=N;i++){

			writeToFile(outputFile,"Nearest neigbor-" + to_string(i) + ":");
			// cout << "Nearest neigbor-" << N << ":";

			if(tempVector.size() >= (unsigned long int)i){

				// if(tempVector.size() == (unsigned long int)N)		
				writeToFile(outputFile,tempVector.at(i-1).second->getID() + "\n");
					// cout << tempVector.at(N-1).second->getID();
				// cout << endl;

				writeToFile(outputFile,"distanceLSH: ");
				// cout << "distanceLSH: ";
				// if(tempVector.size() == (unsigned long int)N)		
					writeToFile(outputFile,to_string(tempVector.at(i-1).first));
					// cout << tempVector.at(N-1).first;
				
				writeToFile(outputFile,"\n");

				auto endHupercube = high_resolution_clock::now();
				
				auto startTrue = high_resolution_clock::now();

				writeToFile(outputFile,"distanceTrue: ");
				// cout << "distanceTrue: ";
				// if(tempVector.size() == (unsigned long int)N)		
					writeToFile(outputFile,to_string(brutekNN(i,&queryItem,dataFile)));
					// cout << brutekNN(N,&queryItem,dataFile);
				// cout << endl;

				writeToFile(outputFile,"\n");

				auto endTrue = high_resolution_clock::now();

				totalHypercube += (double)duration_cast<milliseconds>(endHupercube - startHypercube).count();
				// writeToFile(outputFile,"tHypercube: " + to_string((double)duration_cast<milliseconds>(endHupercube - startHypercube).count()) + "\n");
				// cout << "tLSH: " << (double)duration_cast<milliseconds>(endLSH - startLSH).count() << endl;
				totalTrue += (double)duration_cast<milliseconds>(endTrue - startTrue).count();
				// writeToFile(outputFile,"tTrue: " + to_string((double)duration_cast<milliseconds>(endTrue - startTrue).count()) + "\n");
				// cout << "tTrue: " << (double)duration_cast<milliseconds>(endTrue - startTrue).count() << endl;
			}else{

				writeToFile(outputFile,"\n");
				writeToFile(outputFile,"distanceLSH: NULL\n");
				// cout << "distanceLSH: NULL";
				// cout << endl;

				auto endHupercube = high_resolution_clock::now();
				
				auto startTrue = high_resolution_clock::now();

				writeToFile(outputFile,"distanceTrue: ");
				// cout << "distanceTrue: ";
				// if(tempVector.size() == (unsigned long int)N)		
					writeToFile(outputFile,to_string(brutekNN(i,&queryItem,dataFile)));
				// 	cout << brutekNN(N,&queryItem,dataFile);
				// cout << endl;

				writeToFile(outputFile,"\n");

				auto endTrue = high_resolution_clock::now();
				
				totalHypercube += (double)duration_cast<milliseconds>(endHupercube - startHypercube).count();
				// writeToFile(outputFile,"tHypercube: " + to_string((double)duration_cast<milliseconds>(endHupercube - startHypercube).count()) + "\n");
				// cout << "tLSH: " << (double)duration_cast<milliseconds>(endLSH - startLSH).count() << endl;
				totalTrue += (double)duration_cast<milliseconds>(endTrue - startTrue).count();
				// writeToFile(outputFile,"tTrue: " + to_string((double)duration_cast<milliseconds>(endTrue - startTrue).count()) + "\n");
				// cout << "tTrue: " << (double)duration_cast<milliseconds>(endTrue - startTrue).count() << endl;

				// cout << "tLSH: " << (double)duration_cast<milliseconds>(endLSH - startLSH).count() << endl;
				// cout << "tTrue: " << (double)duration_cast<milliseconds>(endTrue - startTrue).count() << endl;
			}
		}

		writeToFile(outputFile,"tLSH: " + to_string(totalHypercube) + "\n");
		writeToFile(outputFile,"tTrue: " + to_string(totalTrue) + "\n");

		writeToFile(outputFile,to_string(R) + "-near neigbors: \n");
		// cout << R << "-near neigbors: " << endl;
		vector<pair<item*,double>> results = hash->findRange(R,&queryItem);

		if(!results.empty())
			for(unsigned long int i=0;i<results.size();i++)
				if(results.at(i).first != NULL)
					writeToFile(outputFile,results.at(i).first->getID() + "\n");
					// cout << results.at(i).first->getID() << endl;

		// cout << endl;
		writeToFile(outputFile,"\n");
	}
}

int calculateW(string fileName,int flag){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	int totalDist =0;
	int totalW = 0;

	item *firstItem;

	int count =0;

	while(getline(fp,line)){

		if(++count == 1){

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

			firstItem = new item(id,words);
		}

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

		item newItem(id,words);

		totalDist += dist(2,newItem,*firstItem);
		totalW++;
		
		if(count == flag){

			delete firstItem;
			return totalDist/totalW;
		}
	}

	delete firstItem;
	return 0;
}

int getDimension(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	getline(fp,line);

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

	item newItem(id,words);
	return newItem.getDimension();
	
}

void writeToFile(string fileName,string content){

	ofstream file;

	file.open(fileName,fstream::app);
	file << content;
	file.close();
}
