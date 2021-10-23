#include "../headers/main.h"

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
		else if(!strcmp(argv[i],"-R"))
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

	Hash hash(k,L,w,countItems(inputFile)/4);

	readDataset(inputFile,&hash);

	// hash.print();
	answerQueries(hash,queryFile);

	// vector<double> testv;
	// testv.push_back(1.2);
	// testv.push_back(1.4);
	// testv.push_back(1.6);

	// item test("Spyros",testv);

	// cout << "Entering for Spyros:" << endl;
	// cout << G(test,2,4,10) << endl;

	// cout << endl << endl << endl;

	// vector<double> testv2;
	// testv2.push_back(1.2);
	// testv2.push_back(1.4);
	// testv2.push_back(1.6);

	// item test2("Mike",testv2);

	// cout << "Entering for Mike:" << endl;
	// cout << G(test2,2,4,10) << endl;

	return 0;
}