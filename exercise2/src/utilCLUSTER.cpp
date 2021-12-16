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

double distFrechet(item* x,item* y){

	// cout << "Entered for itemX ";
	// x->print();
	// cout << "And for itemY ";
	// y->print();

	// int size = x.getVector()->size()/2;
	// double array[size][size];

	curve* curveX = x->getCurve();
	// cout << "curveX is " << curveX->getID() << endl;
	curve* curveY = y->getCurve();

	// cout << "Entered for itemX ";
	// curveX->print();
	// cout << "And for itemY ";
	// curveY->print();

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

				// cout << "array[1]["<<j-1<<"] is " << array[1][j-1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(1) is " << dist(2,*curveX->getCoordinateat(1),*curveY->getCoordinateat(j)) << endl;
				double useless = max(array[1][j-1],dist(2,*(curveX->getCoordinateat(1)),*(curveY->getCoordinateat(j))));
				// cout << "array[1]["<<j<<"] IS NOW: " << useless << endl;
				array[1][j] = useless;
			}
			else if(i > 1 && j == 1){

				// cout << "array["<<i-1<<"][1] is " << array[i-1][1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) << endl;
				double useless = max(array[i-1][1],dist(2,*(curveX->getCoordinateat(i)),*(curveY->getCoordinateat(1))));
				// cout << "array["<<i<<"][1] IS NOW: " << useless << endl;
				array[i][1] = useless;
			}
			else if(i > 1 && j > 1){

				// cout << "array["<<i-1<<"]["<<j<<"] is " << array[i-1][j] << endl;
				// cout << "array["<<i-1<<"]["<<j-1<<"] is " << array[i-1][j-1] << endl;
				// cout << "array["<<i<<"]["<<j-1<<"] is " << array[i][j-1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j)) << endl;
				double useless = max({array[i-1][j],array[i-1][j-1],array[i][j-1],dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j))});
				// cout << "array["<<i<<"]["<<j<<"] IS NOW: " << useless << endl;
				array[i][j] = useless;
			}

	// cout << "Returning " << array[size-1][size-1] << endl;

	return array[size-1][size-1];
}

double distFrechetBrute(curve* curveX,curve* curveY){

	// cout << "Entered for itemX ";
	// x->print();
	// cout << "And for itemY ";
	// y->print();

	// int size = x.getVector()->size()/2;
	// double array[size][size];

	// Curve* curveX = x->getCurve();
	// cout << "curveX is " << curveX->getID() << endl;
	// Curve* curveY = y->getCurve();

	// cout << "Entered for itemX ";
	// curveX->print();
	// cout << "And for itemY ";
	// curveY->print();

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

				// cout << "array[1]["<<j-1<<"] is " << array[1][j-1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(1) is " << dist(2,*curveX->getCoordinateat(1),*curveY->getCoordinateat(j)) << endl;
				double useless = max(array[1][j-1],dist(2,*(curveX->getCoordinateat(1)),*(curveY->getCoordinateat(j))));
				// cout << "array[1]["<<j<<"] IS NOW: " << useless << endl;
				array[1][j] = useless;
			}
			else if(i > 1 && j == 1){

				// cout << "array["<<i-1<<"][1] is " << array[i-1][1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(1)) << endl;
				double useless = max(array[i-1][1],dist(2,*(curveX->getCoordinateat(i)),*(curveY->getCoordinateat(1))));
				// cout << "array["<<i<<"][1] IS NOW: " << useless << endl;
				array[i][1] = useless;
			}
			else if(i > 1 && j > 1){

				// cout << "array["<<i-1<<"]["<<j<<"] is " << array[i-1][j] << endl;
				// cout << "array["<<i-1<<"]["<<j-1<<"] is " << array[i-1][j-1] << endl;
				// cout << "array["<<i<<"]["<<j-1<<"] is " << array[i][j-1] << endl;
				// cout << "dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j) is " << dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j)) << endl;
				double useless = max({array[i-1][j],array[i-1][j-1],array[i][j-1],dist(2,*curveX->getCoordinateat(i),*curveY->getCoordinateat(j))});
				// cout << "array["<<i<<"]["<<j<<"] IS NOW: " << useless << endl;
				array[i][j] = useless;
			}

	// cout << "Returning " << array[size-1][size-1] << endl;

	return array[size-1][size-1];
}

/* The following function reads the data from the configuration file given and stores them in the
corresponding variables given as parameters. */
void readConf(string fileName,int *K,int *L,int *kLSH,int *M,int *kCUBE,int *probes){

	ifstream fp;
	fp.open(fileName);

	string line, word;
	int target =0;

	/* Read every line of the file. */
	while(getline(fp,line)){

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

/* The following function reads every data from fileName given, and inserts every item in dataset and also a pointer to each
item in Clustering structure. */
void readDatasetCLUSTER(string fileName,Clustering* cluster,vector<item*> *dataset){

	ifstream fp;
	fp.open(fileName);

	string line,id,word;
	int counter =0;

	/* We read the file line by line. */
	while(getline(fp,line)){

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

		/* And then insert pointer to Hash. */
		cluster->insert(newItem);
	}
}

/* The following function is used in order to fill the Clustering structure using the items that exist in dataset. */
void fillDatasetCLUSTER(vector<item*> dataset,Clustering* cluster){

	for(vector<item*>::iterator it = dataset.begin(); it != dataset.end(); it++)
		cluster->insert(*it);
}

item* getRandomItem(vector<item*> i){

	/* We use uniform distribution in order to generate a random t in range [0,w). */
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distance(0,i.size());

	return i.at(distance(generator));
}

int module(int a, int b){
    return (a%b + b) % b;
}

/* The following function is used to produce ν vector. */
vector<double>* produceNdistVector(int dimension,int mean,int stddev){

	default_random_engine generator(random_device{}());
	normal_distribution<double> distribution(/*mean=*/mean, /*standard deviation=*/stddev);

	vector<double> *temp = new vector<double>;

	for(int i=0;i<dimension;i++)
		temp->push_back(distribution(generator));

	return temp;

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

/* The following function implements the main functionality of the clustering part of the project. */
void functionality(string inputFile,string outputFile,int K, int L, int kLSH, int M, int kCUBE, int probes, int w, bool complete, int totalItems, string method, string update){

/*******************LLOYD*****************************/

	vector<item*> dataset;

	/* If method given is Classic(Lloyd) */
	if(method == "Classic"){

		/* Initialize a clustering structure using the parameters that we need from the paramters given. */
		Clustering clustering1(K,L,kLSH,M,kCUBE,probes,w,totalItems);

		/* Fill the structure using the dataset vector. */
		readDatasetCLUSTER(inputFile,&clustering1,&dataset);

		auto startClustering = high_resolution_clock::now();

		/* Initialize clusters using the k-means++ algorithm. */
		clustering1.kMeansPP();
		/* And finally call the assign function in order to fill the clusters. */
		clustering1.Assign("Classic");

		auto endClustering = high_resolution_clock::now();

		writeToFile(outputFile,"Algorithm: Lloyds\n");

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<int,item*> stats = clustering1.getClusterat(i);

			writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
			writeToFile(outputFile,"centroid: ");

			vector<double> *coordinates = stats.second->getVector();

			for(unsigned long int j=0;j<coordinates->size();j++)
				writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
			
			writeToFile(outputFile,"}\n");
		}

		writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

		/* Here we call the silhouette function in order to write the results in the output file. */
		pair<vector<double>,double> test1 = clustering1.Silhouette();

		writeToFile(outputFile,"Silhouette: [");

		vector<double> result = test1.first;

		for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
			writeToFile(outputFile,to_string(*it) + ",");

		writeToFile(outputFile,to_string(test1.second) + "]\n");

		/* If complete flag was given then also write all items of each cluster in the output file. */
		if(complete){

			for(int i=0;i<K;i++){

				writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

				pair<string,vector<string>> result = clustering1.getCompleteClusterat(i);

				writeToFile(outputFile, result.first + ", " );

				for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
					writeToFile(outputFile,(*it) + ",");

				writeToFile(outputFile,"}\n");

			}
		}

		writeToFile(outputFile,"\n");

	}

/*************************LSH************************/
	/* If method given is LSH */
	else if(method == "LSH"){

		/* Initialize a clustering structure using the parameters that we need from the paramters given. */
		Clustering clustering2(K,L,kLSH,M,kCUBE,probes,w,totalItems);

		/* Fill the structure using the dataset vector. */
		readDatasetCLUSTER(inputFile,&clustering2,&dataset);

		auto startClustering = high_resolution_clock::now();

		/* Initialize clusters using the k-means++ algorithm. */
		clustering2.kMeansPP();
		/* And finally call the assign function in order to fill the clusters. */
		clustering2.Assign("LSH");

		auto endClustering = high_resolution_clock::now();

		writeToFile(outputFile,"Algorithm: LSH\n");

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<int,item*> stats = clustering2.getClusterat(i);

			writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
			writeToFile(outputFile,"centroid: ");

			vector<double> *coordinates = stats.second->getVector();

			for(unsigned long int j=0;j<coordinates->size();j++)
				writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
			
			writeToFile(outputFile,"}\n");
		}

		writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

		/* Here we call the silhouette function in order to write the results in the output file. */
		pair<vector<double>,double> test1 = clustering2.Silhouette();

		writeToFile(outputFile,"Silhouette: [");

		vector<double> result = test1.first;

		for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
			writeToFile(outputFile,to_string(*it) + ",");

		writeToFile(outputFile,to_string(test1.second) + "]\n");

		/* If complete flag was given then also write all items of each cluster in the output file. */
		if(complete){

			for(int i=0;i<K;i++){

				writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

				pair<string,vector<string>> result = clustering2.getCompleteClusterat(i);

				writeToFile(outputFile, result.first + ", " );

				for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
					writeToFile(outputFile,(*it) + ",");

				writeToFile(outputFile,"}\n");

			}
		}

		writeToFile(outputFile,"\n");
	}

/********************HYPERCUBE***************/

	/* If method given is Hypercube */
	else{

		/* Initialize a clustering structure using the parameters that we need from the paramters given. */
		Clustering clustering3(K,L,kLSH,M,kCUBE,probes,w,totalItems);

		/* Fill the structure using the dataset vector. */
		readDatasetCLUSTER(inputFile,&clustering3,&dataset);

		auto startClustering = high_resolution_clock::now();

		/* Initialize clusters using the k-means++ algorithm. */
		clustering3.kMeansPP();
		/* And finally call the assign function in order to fill the clusters. */
		clustering3.Assign("Hypercube");

		auto endClustering = high_resolution_clock::now();

		writeToFile(outputFile,"Algorithm: Hypercube\n");

		for(int i=0;i<K;i++){

			writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

			pair<int,item*> stats = clustering3.getClusterat(i);

			writeToFile(outputFile,"size: " + to_string(stats.first) + ",");
			writeToFile(outputFile,"centroid: ");

			vector<double> *coordinates = stats.second->getVector();

			for(unsigned long int j=0;j<coordinates->size();j++)
				writeToFile(outputFile,to_string(coordinates->at(j)) + " ");
			
			writeToFile(outputFile,"}\n");
		}

		writeToFile(outputFile,"clustering_time: " + to_string((double)duration_cast<seconds>(endClustering - startClustering).count()) + "\n");

		/* Here we call the silhouette function in order to write the results in the output file. */
		pair<vector<double>,double> test1 = clustering3.Silhouette();

		writeToFile(outputFile,"Silhouette: [");

		vector<double> result = test1.first;

		for(vector<double>::iterator it = result.begin(); it != result.end(); it++)
			writeToFile(outputFile,to_string(*it) + ",");

		writeToFile(outputFile,to_string(test1.second) + "]\n");

		/* If complete flag was given then also write all items of each cluster in the output file. */
		if(complete){

			for(int i=0;i<K;i++){

				writeToFile(outputFile,"CLUSTER-" + to_string(i) + " {");

				pair<string,vector<string>> result = clustering3.getCompleteClusterat(i);

				writeToFile(outputFile, result.first + ", " );

				for(vector<string>::iterator it = result.second.begin(); it != result.second.end(); it++)
					writeToFile(outputFile,(*it) + ",");

				writeToFile(outputFile,"}\n");

			}
		}
	}

	for(vector<item*>::iterator it = dataset.begin(); it != dataset.end(); it++)
		delete (*it);
}

/* The following function counts the total amount of items that exist in a file given. */
int countItems(string fileName){

	ifstream fp;
	fp.open(fileName);

	string line;
	int n =0;

	while(getline(fp,line)) n++;

	return n;

}