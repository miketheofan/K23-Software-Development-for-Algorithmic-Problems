#include "mainSEARCH.h"

int main(int argc,char** argv){

	string inputFile = "";
	string queryFile = "";
	string outputFile = "";
	int k;
	int L = 5;
	int M = 10;
	int probes = 2;
	double delta;
	string algorithm = "";
	string metric = "";

	/* Get the data we need from argv. */
	for(int i=0;i<argc;i++)
		if(!strcmp(argv[i],"-i"))
			inputFile = argv[++i];
		else if(!strcmp(argv[i],"-q"))
			queryFile = argv[++i];
		else if(!strcmp(argv[i],"-o"))
			outputFile = argv[++i];
		else if(!strcmp(argv[i],"-k"))
			k = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-L"))
			L = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-M"))
			M = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-probes"))
			probes = stoi(argv[++i]);
		else if(!strcmp(argv[i],"-delta"))
			delta = stod(argv[++i]);
		else if(!strcmp(argv[i],"-algorithm"))
			algorithm = argv[++i];
		else if(!strcmp(argv[i],"-metric"))
			metric = argv[++i];

	/* We initialize w as a random number between 2 and 6, as was suggested in the paper. */
	int w = rand()%6+2;

	vector<item*> dataset;

	Hash* hash;
	HyperCube* cube;

	if(algorithm == "LSH"){

		k = 4;
		hash = new Hash(k,L,w,countItems(inputFile)/4,getDimension(inputFile));
		readDataset(inputFile,hash,&dataset);		
	
	}else if(algorithm == "Hypercube"){ 

		k = 14;		
		cube = new HyperCube(k,w,M,probes,getDimension(inputFile));
		readDataset(inputFile,cube,&dataset);

	}else if(algorithm != "Fretchet"){

		cerr << "Wrong algorithm given as parameter." << endl;
		return -1;
	}	

	/* First we check if inputFile was given by the user. */
	if(inputFile == ""){

		bool flag = true;

		/* If it was not given, ask him for the path of the file, and do this until path given actually exists. */
		do{

			cout << "Give me the path of the dataset file: " << endl;
			cin >> inputFile;

			ifstream file1(inputFile);
			if(!file1){

				cerr << "inputFile does not exist.";
				flag = false;
			}

		}while(flag == false);
	
	}

	string check;

	do{

		/* We check if queryFile was given by the user. */
		if(queryFile == ""){

			bool flag = true;

			/* If it was not given, ask him for the path of the file, and do this until path given actually exists. */
			do{

				cout << "Give me the path of the query file: " << endl;
				cin >> queryFile;

				ifstream file1(queryFile);
				if(!file1){

					cerr << "queryFile does not exist.";
					flag = false;
				}

			}while(flag == false);

		}

		/* We check if outputFile was given by the user. */
		if(outputFile == ""){

			bool flag = true;

			/* If it was not given, ask him for the path of the file, and do this until path given actually exists. */
			do{

				cout << "Give me the path of the output file: " << endl;
				cin >> outputFile;

				ifstream file1(outputFile);
				if(!file1){

					cerr << "outputFile does not exist.";
					flag = false;
				}

			}while(flag == false);

		}

		ofstream file(outputFile);
		file.close();

		if(algorithm == "LSH") 
			answerQueries(hash,queryFile,inputFile,1,outputFile);
		else if(algorithm == "Hypercube")
			answerQueries(cube,queryFile,inputFile,1,outputFile);
	
		string inputFile = "";
		string queryFile = "";
		string outputFile = "";

		/* We delete every memory that was allocated for every item read from the inputFile. */
		for(unsigned long int i=0;i<dataset.size();i++)
			delete(dataset.at(i));

		delete hash;
		delete cube;

		cout << "Do you want to run the program with different data and queries(Y/N): ";
		cin >> check;

	}while(check == "Y");

	return 0;
}