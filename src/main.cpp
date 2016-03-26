#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "ReceptiveFields.h"
using namespace std;

int main(){
	cout << "Test" << endl;

	ReceptiveFields* RF = new ReceptiveFields(45, 180, 20, 0.025, 0.2, 100, 1000);
	RF->toString();
	cout << "lala";
	//Read data file
	vector<string> inputStrings;
	ifstream filein;
	filein.open("filename.extension");
	int index = 0;
	while(!filein.eof){
		getline(filein,inputStrings[int];
		index++;
	}
	stringstream ss();
	vector<string> splitStrings;
	string buff;
	for(int i = 0; i < inputString.size(); i++){
		ss(inputStrings[i]);
		while( ss >> buff){
			splitString.push_back(buff);
		}
		//call to Receptive Fields activation function
	}
	return 0;
}
