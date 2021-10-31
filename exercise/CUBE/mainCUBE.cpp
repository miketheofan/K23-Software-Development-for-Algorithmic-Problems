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

		bool flag = true;

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

	int dimension = getDimension(inputFile);

	int w = calculateW(inputFile,200);

	string check;

	do{

		HyperCube cube(k,w,M,probes,128);

		vector<item*> dataset;
		
		readDatasetCUBE(inputFile,&cube,&dataset);

		if(queryFile == ""){

			bool flag = true;

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

		if(outputFile == ""){

			bool flag = true;

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

		answerQueries(&cube,queryFile,inputFile,M,N,R,outputFile);

		string inputFile = "";
		string queryFile = "";
		string outputFile = "";

		for(unsigned long int i=0;i<dataset.size();i++)
			delete(dataset.at(i));

		cout << "Do you want to run the program with different data and queries(Y/N): ";
		cin >> check;

	}while(check == "Y");

	return 0;
}