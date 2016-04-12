#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ReceptiveFields.h"
using namespace std;

int main(){
	cout << "Test" << endl;

	ReceptiveFields* RF = new ReceptiveFields(45, 180, 20, 0.025, 0.2, 100, 1000);
	//Read data file
	string inputString;
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open("runbot_data_edited.log");
	while(getline(filein,inputString)){
		stringstream lineStream(inputString);
		splitStrings.clear();
		while(getline(lineStream, token, ',')){
			splitStrings.push_back(token);
		}
		//call to receptiveFields
	}
	filein.close();
	return 0;
}
