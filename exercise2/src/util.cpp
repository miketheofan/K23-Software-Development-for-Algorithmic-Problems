#include "../headers/util.h"

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

double distFrechet(item* x,item* y){

	// cout << "Entered for itemX ";
	// x.print();
	// cout << "And for itemY ";
	// y.print();

	double infinite = std::numeric_limits<int>::max();

	// int size = x.getVector()->size()/2;
	// double array[size][size];

	Curve* curveX = x->getCurve();
	// cout << "curveX is " << curveX->getID() << endl;
	Curve* curveY = y->getCurve();

	if(curveX->getSize() != curveY->getSize()){

		cerr << "Cannot compute Frechet distance between vertexes from different dimensions." << endl;
		return 0;
	}

	int size = curveX->getSize();

	double array[size][size];
	// for(int i=0;i<size;i++)
	// 	for(int j=0;j<size;j++)
	// 		array[i][j] = 0;

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			if(i == 0 && j == 0)
				array[i][j] = dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j));
			else if(i == 1 && j > 1){

				cout << "array[1]["<<j-1<<"] is " << array[1][j-1] << endl;
				cout << "dist(2,*curveX->getCoordinateat(1) is " << dist(2,*curveX->getCoordinateat(1),*curveY->getCoordinateat(j)) << endl;
				cout << "array[1]["<<j<<"] IS NOW" << max(array[1][j-1],dist(2,*(curveX->getCoordinateat(1)),*(curveY->getCoordinateat(j)))) << endl;
				array[1][j] = max(array[1][j-1],dist(2,*(curveX->getCoordinateat(1)),*(curveY->getCoordinateat(j))));
			}
			else if(i > 1 && j == 1){

				cout << "array["<<i-1<<"][1] is " << array[i-1][1] << endl;
				cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) << endl;
				cout << "array["<<i<<"][1] IS NOW: " << max(array[i-1][1],dist(2,*(curveX->getCoordinateat(i)),*(curveY->getCoordinateat(1)))) << endl;
				array[i][1] = max(array[i-1][1],dist(2,*(curveX->getCoordinateat(i)),*(curveY->getCoordinateat(1))));
			}
			else if(i > 1 && j > 1){

				cout << "array["<<i-1<<"]["<<j<<"] is " << array[i-1][j] << endl;
				cout << "array["<<i-1<<"]["<<j-1<<"] is " << array[i-1][j-1] << endl;
				cout << "array["<<i<<"]["<<j-1<<"] is " << array[i][j-1] << endl;
				cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j)) << endl;
				cout << "array["<<i<<"]["<<j<<"] IS NOW: " << max({array[i-1][j],array[i-1][j-1],array[i][j-1],dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j))}) << endl;
				array[i][j] = max({array[i-1][j],array[i-1][j-1],array[i][j-1],dist(2,*(curveX->getCoordinateat(i)),*(curveY->getCoordinateat(j)))});
			}
			// else
			// 	array[i][j] = infinite;

	cout << "Returning " << array[size][size] << endl;

	return array[size][size];
}

/* The following function reads every data from fileName given, and inserts every item in dataset and also a pointer to each
item in HyperCube structure. */
void readDataset(string fileName,HyperCube* cube,vector<item*> *dataset){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	/* We read the file line by line. */
	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		/* We read every word of each line. */
		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		/* We create an item *only once* and insert in dataset. */
		item* newItem = new item(id,words);
		dataset->push_back(newItem);

		/* And then insert pointer to HyperCube. */
		cube->insert(newItem);
	}
}

/* The following function reads every data from fileName given, and inserts every item in dataset and also a pointer to each
item in Hash structure. */
void readDataset(string fileName,Hash* hash,vector<item*> *dataset){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	/* We read the file line by line. */
	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		/* We read every word of each line. */
		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		/* We create an item *only once* and insert in dataset. */
		item* newItem = new item(id,words);
		dataset->push_back(newItem);

		/* And then insert pointer to HyperCube. */
		hash->insert(newItem);
	}
}

void readDataset(string fileName,Discrete* disc,vector<item*> *dataset){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	/* We read the file line by line. */
	while( getline(fp,line) ){

		vector<double> words;
		stringstream linestream(line);

		/* We read every word of each line. */
		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		/* We create an item *only once* and insert in dataset. */
		item* newItem = new item(id,words);
		dataset->push_back(newItem);

		/* And then insert pointer to LSH for Discrete Frechet. */
		disc->insert(newItem);
	}
}

/* The following function is used to produce ν vector. */
vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(mean,stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}

int module(int a, int b){
    return (a%b + b) % b;
}

/* The following function counts the total amount of items that exist in a file given. */
int countItems(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line;
	int n =0;

	while( getline(fp,line) )
		n++;

	return n;

}

/* The following function implements the main functionality of answering the queries. */
void answerQueries(HyperCube* cube,string fileName,string dataFile,int M,/*int N,int R,*/string outputFile){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	double totalApproximate =0;
	double totalTrue =0;
	double totalItems =0;

	/* We get every line (query) of the file given. */
	while(getline(fp,line)){

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

		/* Statically create query item. */
		item queryItem(id,words);

		/* And produce the output that was given in the paper of the project. 
		We use writeToFile function in order to write output in output.txt file. */
		writeToFile(outputFile,"Query: " + queryItem.getID() + "\n");

		auto startHypercube = high_resolution_clock::now();
		vector<pair<double,item*>> tempVector = cube->findkNN(&queryItem,M,1);
		auto endHypercube = high_resolution_clock::now();

		auto startTrue = high_resolution_clock::now();
		vector<pair<double,item*>> trueResults = brutekNN(1,&queryItem,dataFile);
		auto endTrue = high_resolution_clock::now();

		writeToFile(outputFile,"Approximate Nearest neigbor: ");
		writeToFile(outputFile,tempVector.at(0).second->getID() + "\n");
		writeToFile(outputFile,"True Nearest neigbor: ");
		writeToFile(outputFile,trueResults.at(0).second->getID());
		writeToFile(outputFile,"\n");
			
		writeToFile(outputFile,"distanceApproximate: ");
		writeToFile(outputFile,to_string(tempVector.at(0).first));
		writeToFile(outputFile,"\n");

		writeToFile(outputFile,"distanceTrue: ");
		writeToFile(outputFile,to_string(trueResults.at(0).first));
		writeToFile(outputFile,"\n");

		totalItems++;
		totalApproximate += (double)duration_cast<milliseconds>(endHypercube - startHypercube).count();
		totalTrue += (double)duration_cast<milliseconds>(endTrue - startTrue).count();
		
		writeToFile(outputFile,"\n");

	}

	writeToFile(outputFile,"tApproximateAverage: " + to_string(totalApproximate/totalItems) + "\n");
	writeToFile(outputFile,"tTrueAverage: "+ to_string(totalTrue/totalItems) + "\n");
}

/* The following function implements the main functionality of answering the queries. */
void answerQueries(Hash* hash,string fileName,string dataFile,int M,/*int N,int R,*/string outputFile){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	double totalApproximate =0;
	double totalTrue =0;
	double totalItems =0;

	/* We get every line (query) of the file given. */
	while(getline(fp,line)){

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

		/* Statically create query item. */
		item queryItem(id,words);

		/* And produce the output that was given in the paper of the project. 
		We use writeToFile function in order to write output in output.txt file. */
		writeToFile(outputFile,"Query: " + queryItem.getID() + "\n");

		auto startHypercube = high_resolution_clock::now();
		vector<pair<double,item*>> tempVector = hash->findkNN(1,&queryItem);
		auto endHypercube = high_resolution_clock::now();

		auto startTrue = high_resolution_clock::now();
		vector<pair<double,item*>> trueResults = brutekNN(1,&queryItem,dataFile);
		auto endTrue = high_resolution_clock::now();

		writeToFile(outputFile,"Approximate Nearest neigbor: ");
		writeToFile(outputFile,tempVector.at(0).second->getID() + "\n");
		writeToFile(outputFile,"True Nearest neigbor: ");
		writeToFile(outputFile,trueResults.at(0).second->getID());
		writeToFile(outputFile,"\n");
			
		writeToFile(outputFile,"distanceApproximate: ");
		writeToFile(outputFile,to_string(tempVector.at(0).first));
		writeToFile(outputFile,"\n");

		writeToFile(outputFile,"distanceTrue: ");
		writeToFile(outputFile,to_string(trueResults.at(0).first));
		writeToFile(outputFile,"\n");

		totalItems++;
		totalApproximate += (double)duration_cast<milliseconds>(endHypercube - startHypercube).count();
		totalTrue += (double)duration_cast<milliseconds>(endTrue - startTrue).count();

		writeToFile(outputFile,"\n");
	}

	writeToFile(outputFile,"tApproximateAverage: " + to_string(totalApproximate/totalItems) + "\n");
	writeToFile(outputFile,"tTrueAverage: "+ to_string(totalTrue/totalItems) + "\n");
}

void answerQueries(Discrete* disc,string fileName,string dataFile,int M,/*int N,int R,*/string outputFile){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	double totalApproximate =0;
	double totalTrue =0;
	double totalItems =0;

	/* We get every line (query) of the file given. */
	while(getline(fp,line)){

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

		/* Statically create query item. */
		item queryItem(id,words);

		/* And produce the output that was given in the paper of the project. 
		We use writeToFile function in order to write output in output.txt file. */
		writeToFile(outputFile,"Query: " + queryItem.getID() + "\n");

		auto startHypercube = high_resolution_clock::now();
		pair<double,Curve*> tempPair = disc->findNN(&queryItem);
		auto endHypercube = high_resolution_clock::now();

		auto startTrue = high_resolution_clock::now();
		vector<pair<double,item*>> trueResults = brutekNN(1,&queryItem,dataFile);
		auto endTrue = high_resolution_clock::now();

		writeToFile(outputFile,"Approximate Nearest neigbor: ");
		writeToFile(outputFile,tempPair.second->getID() + "\n");
		writeToFile(outputFile,"True Nearest neigbor: ");
		writeToFile(outputFile,trueResults.at(0).second->getID());
		writeToFile(outputFile,"\n");
			
		writeToFile(outputFile,"distanceApproximate: ");
		writeToFile(outputFile,to_string(tempPair.first));
		writeToFile(outputFile,"\n");

		writeToFile(outputFile,"distanceTrue: ");
		writeToFile(outputFile,to_string(trueResults.at(0).first));
		writeToFile(outputFile,"\n");

		totalItems++;
		totalApproximate += (double)duration_cast<milliseconds>(endHypercube - startHypercube).count();
		totalTrue += (double)duration_cast<milliseconds>(endTrue - startTrue).count();

		writeToFile(outputFile,"\n");
	}

	writeToFile(outputFile,"tApproximateAverage: " + to_string(totalApproximate/totalItems) + "\n");
	writeToFile(outputFile,"tTrueAverage: "+ to_string(totalTrue/totalItems) + "\n");
}

/* The following function returns the dimension in which items from inputFile are. */
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

/* The following function is used in order to write output to outputFile given. */
void writeToFile(string fileName,string content){

	ofstream file;

	file.open(fileName,fstream::app);
	file << content;
	file.close();
}
