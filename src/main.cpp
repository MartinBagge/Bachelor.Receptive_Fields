#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ReceptiveFields.h"
#include <gtest/gtest.h>

using namespace std;
/*
TEST(Re){

}
*/

int main(){
	cout << "Test" << endl;

	ReceptiveFields* RF = new ReceptiveFields(60, 120, 200, 0.025, 0.6, 1000, 266);
	//Read data file
	string inputString;
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open("runbot_data_multiplied.log");
	while(getline(filein,inputString)){
		stringstream lineStream(inputString);
		splitStrings.clear();
		while(getline(lineStream, token, ',')){
			splitStrings.push_back(token);
		}
		RF->generateTarget(atof(splitStrings[8].c_str()));
		RF->generateAlfaPattern();
	}
	filein.close();
	RF->createGaussianKernels();
	//RF->toString();
	return 0;
}
