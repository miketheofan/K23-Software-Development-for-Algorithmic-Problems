#include "../headers/util.h"

double dist(item x,item y){

	if(x.getVector().size() != y.getVector().size()){

		cerr << "Cannot compute Euclidean Distance between vertexes from different dimensions." << endl;
		return 0;
	}

	unsigned long int d = x.getVector().size();
	double result = 0.0;

	for(unsigned long int i = 0;i<d;i++)
		result += pow(x.getVector()[i]-y.getVector()[i],2);
	
	return sqrt(result);
}

void readDataset(string fileName){

	ifstream fp;
	fp.open(fileName);

	vector<double> words;
	string line,id,word;// , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8;
	int counter =0;

	while( getline(fp,line) ){

		stringstream linestream(line);

		while(linestream >> word){

			if(++counter == 1){

				id = word;
				continue;
			}

			words.push_back(stod(word));

		}

		counter =0;

		item temp(id,words);
		temp.print();
	}
}