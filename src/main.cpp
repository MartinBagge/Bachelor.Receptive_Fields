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

	ReceptiveFields RF(60, 120, 40, 0.1, 0.4, 500, 85, true);
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
				RF.generateTarget(atof(splitStrings[i].c_str()));
			}
			std::cout << "fileread done" << std::endl;
		//}
	int tmp = 1;
	for(int i = 0; i < 85; i++){
		RF.createStep(tmp);
		tmp++;
	}
	RF.applyDeltaRule();
	RF.toString();
	return 0;
}
