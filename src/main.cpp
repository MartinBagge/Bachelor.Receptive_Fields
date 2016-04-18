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

	ReceptiveFields* RF = new ReceptiveFields(60, 120, 200, 1, 0.1, 1000, 1061);
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
		RF->generateTarget(atof(splitStrings[5].c_str()));
	}
	filein.close();
	RF->generateAlfaPattern();
	RF->createGaussianKernels();
	RF->toString();
	return 0;
}
