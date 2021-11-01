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

	int w = rand()%6+2;

	string check;

	do{

		Hash hash(k,L,w,countItems(inputFile)/4,128);

		vector<item*> dataset;

		readDatasetLSH(inputFile,&hash,&dataset);

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

		// hash.print();
		answerQueries(&hash,queryFile,inputFile,N,R,outputFile);
		
		string inputFile = "";
		string queryFile = "";
		string outputFile = "";

		for(unsigned long int i=0;i<dataset.size();i++)
			delete(dataset.at(i));

	}while(check == "Y");

	return 0;
}