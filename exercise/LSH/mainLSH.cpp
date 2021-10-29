#include "./mainLSH.h"

int main(int argc,char **argv){

    srand(time(0));

	string inputFile = "";
	string queryFile = "";
	int k = 4;
	int L = 5;
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
		else if(!strcmp(argv[i],"-L"))
			L = stoi(argv[++i]);
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

	int w = rand()%6+2;

	Hash hash(k,L,w,countItems(inputFile)/4,128);

	vector<item*> dataset;

	readDatasetLSH(inputFile,&hash,&dataset);

	// hash.print();
	answerQueries(&hash,queryFile,inputFile,N,R);
	
	// hash.print();

	for(unsigned long int i=0;i<dataset.size();i++)
		delete(dataset.at(i));

	return 0;
}