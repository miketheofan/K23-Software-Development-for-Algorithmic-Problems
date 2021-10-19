#include "../headers/main.h"

int main(int argc,char **argv){

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

	vector<double> vec1;
	vec1.push_back(0);
	vec1.push_back(-2);
	vec1.push_back(7);

	vector<double> vec2;
	vec2.push_back(8);
	vec2.push_back(4);
	vec2.push_back(3);

	item x("lol",vec1);
	item y("lol2",vec2);
	cout << dist(x,y) << endl;

	return 0;
}