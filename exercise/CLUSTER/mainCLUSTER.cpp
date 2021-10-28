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

	readConf(configurationFile,&K,&L,&kLSH,&M,&kCUBE,&probes);

	Clustering clustering(K,L,kLSH,M,kCUBE,probes);

	readDatasetCLUSTER(inputFile,&clustering);

	clustering.kMeansPP();
	clustering.Assign();

	clustering.print();

	return 0;
}