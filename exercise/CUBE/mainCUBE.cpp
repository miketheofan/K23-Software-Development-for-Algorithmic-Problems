#include "./mainCUBE.h"

int main(int argc,char **argv){

	string inputFile = "";
	string queryFile = "";
	int k = 14;
	int M = 10;
	int probes = 2;
	string outputFile = "";
	int N = 1;
	int R = 10000;

	/* Get the data we need from argv. */
	for(int i=0;i<argc;i++)
		if(!strcmp(argv[i],"-i"))
			inputFile = argv[++i];
		else if(!strcmp(argv[i],"-q"))
			queryFile = argv[++i];
		else if(!strcmp(argv[i],"-k"))
			k = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-probes"))
			probes = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-o"))
			outputFile = argv[++i];
		else if(!strcmp(argv[i],"-N"))
			N = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-r"))
			R = stoi(argv[++i]);

	if(inputFile == ""){

		cerr << "Input file not given." << endl;
		exit(-1);
	}
	if(queryFile == ""){

		cerr << "Query file not given." << endl;
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

	ifstream file2(queryFile);
	if(!file2){

		cerr << "Query file does not exist." << endl;
		exit(-1);
	}	

	cout << "We here" << endl;

	return 0;
}