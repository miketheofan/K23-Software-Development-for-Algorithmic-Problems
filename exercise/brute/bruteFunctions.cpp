#include "../headers/bruteFunctions.h"

double bruteNN(item* i,string fileName){

	ifstream fp;
	fp.open(fileName);

	double minimum = numeric_limits<int>::max();
	double distance;

	string line,id,word;
	int counter =0;

	while( getline(fp,line) ){

		vector<double> words;
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

		distance = dist(2,*i,temp);

		if(dist(2,*i,temp) < minimum)
			minimum = distance;

	}

	return minimum;
}

double brutekNN(int k,item* i,string fileName){

	ifstream fp;
	fp.open(fileName);

	double minimum = numeric_limits<int>::max();
	double distance;

	string line,id,word;
	int counter =0;

	vector<pair<double,item*> > queries;

	while( getline(fp,line) ){

		vector<double> words;
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

		distance = dist(2,*i,temp);

		if(distance < minimum){

			if((int)queries.size() == k){

				queries.pop_back();
				queries.push_back(make_pair(distance,i));

				sort(queries.begin(),queries.end());
				
				minimum	= distance;

			}else
				queries.push_back(make_pair(distance,i));
		}


	}

	return queries.at(k-1).first;

}