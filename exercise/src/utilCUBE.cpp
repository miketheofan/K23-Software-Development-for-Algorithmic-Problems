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

/* The following function reads every data from fileName given, and inserts every item in dataset and also a pointer to each
item in HyperCube structure. */
void readDatasetCUBE(string fileName,HyperCube* cube,vector<item*> *dataset){

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

/* The following function is used to produce ν vector. */
vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(mean,stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

}

/* The following function implements the main functionality of answering the queries. */
void answerQueries(HyperCube *cube,string fileName,string dataFile,int M,int N,int R,string outputFile){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

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
		vector<pair<double,item*>> tempVector = cube->findkNN(&queryItem,M,N);
		auto endHypercube = high_resolution_clock::now();

		auto startTrue = high_resolution_clock::now();
		vector<pair<double,item*>> trueResults = brutekNN(N,&queryItem,dataFile);
		auto endTrue = high_resolution_clock::now();

		for(int i=1;i<=N;i++){

			writeToFile(outputFile,"Nearest neigbor-" + to_string(i) + ":");

			if(tempVector.size() >= (unsigned long int)i){

				writeToFile(outputFile,tempVector.at(i-1).second->getID() + "\n");
				writeToFile(outputFile,"distanceHypercube: ");
				writeToFile(outputFile,to_string(tempVector.at(i-1).first));
				writeToFile(outputFile,"\n");

				writeToFile(outputFile,"distanceTrue: ");
				writeToFile(outputFile,to_string(trueResults.at(i-1).first));
				writeToFile(outputFile,"\n");

			}else{

				writeToFile(outputFile,"\n");
				writeToFile(outputFile,"distanceHypercube: NULL\n");

				writeToFile(outputFile,"distanceTrue: ");
				writeToFile(outputFile,to_string(trueResults.at(i-1).first));
				writeToFile(outputFile,"\n");

			}
		}

		writeToFile(outputFile,"tHypercube: " + to_string((double)duration_cast<milliseconds>(endHypercube - startHypercube).count()) + "\n");
		writeToFile(outputFile,"tTrue: " + to_string((double)duration_cast<milliseconds>(endTrue - startTrue).count()) + "\n");

		writeToFile(outputFile,to_string(R) + "-near neigbors: \n");
		vector<pair<item*,double>> results = cube->findRange(R,&queryItem,M);

		if(!results.empty())
			for(unsigned long int i=0;i<results.size();i++)
				if(results.at(i).first != NULL)
					writeToFile(outputFile,results.at(i).first->getID() + "\n");

		writeToFile(outputFile,"\n");
	}
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
