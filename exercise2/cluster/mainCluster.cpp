#include "./mainCluster.h"

int main(int argc,char **argv){

	string inputFile = "";
	string configurationFile = "";
	string outputFile = "";
	string update = "";
	string assignment = "";
	int K;
	int L = 3;
	int kLSH = 4;
	int M = 10;
	int kCUBE = 3;
	int probes = 2;
	bool complete = false;
	bool silhouette = false;

	/* Get the data we need from argv. */
	for(int i=0;i<argc;i++)
		if(!strcmp(argv[i],"-i"))
			inputFile = argv[++i];
		else if(!strcmp(argv[i],"-c"))
			configurationFile = argv[++i];
		else if(!strcmp(argv[i],"-o"))
			outputFile = argv[++i];
		else if(!strcmp(argv[i],"-update")){
			update = argv[++i];
			update += " "; 
			update += argv[++i];
		}else if(!strcmp(argv[i],"-assignment"))
			assignment = argv[++i];
		else if(!strcmp(argv[i],"-complete"))
			complete = true;
		else if(!strcmp(argv[i],"-silhouette"))
			silhouette = true;

	/* If input file not given then exit program. */
	if(inputFile == ""){

		cerr << "Input file not given." << endl;
		exit(-1);
	}

	/* If configuration file not given then exit program. */
	if(configurationFile == ""){

		cerr << "Configuration file not given." << endl;
		exit(-1);
	}

	/* If output file not given then exit program. */
	if(outputFile == ""){

		cerr << "Output file not given." << endl;
		exit(-1);
	}

	/* If input file does not exist then exit program. */
	ifstream file1(inputFile);
	if(!file1){

		cerr << "Input file does not exist." << endl;
		exit(-1);
	}

	/* If configuration file does not exist then exit program. */
	ifstream file2(configurationFile);
	if(!file2){

		cerr << "Configuration file does not exist." << endl;
		exit(-1);
	}

	ofstream file(outputFile);
	file.close();

	int totalItems = countItems(inputFile);

	/* We initialize w as a random number between 2 and 6, as was suggested in the paper. */
	int w = rand()%6+2;

	/* We use readConf function in order to read the parameters we need for the execution of the program, from
	the configuration file. */
	readConf(configurationFile,&K,&L,&kLSH,&M,&kCUBE,&probes);

	/* We start the main functionality of the program. */
	functionality(inputFile,outputFile,K, L, kLSH, M, kCUBE, probes, w, complete,totalItems,assignment,update);

	return 0;
}