#include "./mainCLUSTER.h"

int main(int argc,char **argv){

	string inputFile = "";
	string configurationFile = "";
	string outputFile = "";
	string method = "";
	int K;
	int L = 3;
	int kLSH = 4;
	int M = 10;
	int kCUBE = 3;
	int probes = 2;
	bool complete = false;

	/* Get the data we need from argv. */
	for(int i=0;i<argc;i++)
		if(!strcmp(argv[i],"-i"))
			inputFile = argv[++i];
		else if(!strcmp(argv[i],"-c"))
			configurationFile = argv[++i];
		else if(!strcmp(argv[i],"-o"))
			outputFile = argv[++i];
		else if(!strcmp(argv[i],"-m"))
			method = argv[++i];
		else if(!strcmp(argv[i],"-complete"))
			complete = true;

	if(inputFile == ""){

		cerr << "Input file not given." << endl;
		exit(-1);
	}
	if(configurationFile == ""){

		cerr << "Configuration file not given." << endl;
		exit(-1);
	}
	if(outputFile == ""){

		cerr << "Output file not given." << endl;
		exit(-1);
	}

	ifstream file1(inputFile);
	if(!file1){

		cerr << "Input file does not exist." << endl;
		exit(-1);
	}

	ifstream file2(configurationFile);
	if(!file2){

		cerr << "Configuration file does not exist." << endl;
		exit(-1);
	}

	ofstream file(outputFile);
	file.close();

	int totalItems = countItems(inputFile);

	int w = rand()%6+2;

	readConf(configurationFile,&K,&L,&kLSH,&M,&kCUBE,&probes);

	functionality(inputFile,outputFile,K, L, kLSH, M, kCUBE, probes, w, complete,totalItems,method);

	// Clustering clustering(K,L,kLSH,M,kCUBE,probes,w);

	// vector<item*> dataset;

	// readDatasetCLUSTER(inputFile,&clustering,&dataset);
	// //readDatasetCUBE()

	// clustering.kMeansPP();
	// clustering.Assign("Hypercube");

	// clustering.print();

	// pair<vector<double>,double> test = clustering.Silhouette();

	// cout << "Algorithm: " << endl;
	// cout << "Silhouette: [";

	// vector<double> result = test.first;

	// for(vector<double>::iterator it = result.begin(); it != result.end(); it++){

	// 	cout << (*it) << ",";
	// }

	// cout << test.second << "]" << endl;

	// for(unsigned long int i=0;i<dataset.size();i++)
	// 	delete(dataset.at(i));

	return 0;
}