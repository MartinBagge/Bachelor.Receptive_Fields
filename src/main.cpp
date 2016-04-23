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

	ReceptiveFields* RF = new ReceptiveFields(60, 120, 40, 0.1, 0.4, 10000, 85);
	//Read data file
	string inputString;
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open("runbot_leftknee_output.log");
	//while(getline(filein,inputString)){
			//stringstream lineStream(inputString);
			//splitStrings.clear();
	std::cout << "fileread" << std::endl;
			while(getline(filein, token, ',')){
				splitStrings.push_back(token);
			}
			for(int i = 0; i < splitStrings.size(); i++){
				RF->generateTarget(atof(splitStrings[i].c_str()));
			}
			std::cout << "fileread done" << std::endl;
		//}
	std::cout << splitStrings.size() << std::endl;
	RF->generateAlfaPattern();

	RF->createGaussianKernels();
	RF->toString();
	cout << "returning 0" << endl;
	return 0;
}
