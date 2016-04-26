#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ReceptiveFields.h"
#include <gtest/gtest.h>
#include <time.h>

using namespace std;
/*
TEST(Re){

}
*/

int main(){
	int iterations = 500000;
	bool gpu = true;
	int blocks = 86;
	ReceptiveFields RF(60, 120, 40, 0.1, 0.4, iterations, 85, gpu, blocks);
	string inputString;
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open("runbot_leftknee_output.log");
	while(getline(filein, token, ',')){
		splitStrings.push_back(token);
	}
	for(int i = 0; i < splitStrings.size(); i++){
		RF.generateTarget(atof(splitStrings[i].c_str()));
	}
		//}
	std::cout << iterations << std::endl;
	std::cout << "gpu: " << gpu << std::endl;
	std::cout << "blocks: " << blocks << std::endl;
	for (int i = 0; i < 10; i++){
		clock_t tstart = clock();
		int tmp = 1;
		for(int i = 0; i < 85; i++){
			RF.createStep(tmp);
			tmp++;
		}
		RF.applyDeltaRule();
		std::cout << "Time: " << ((double)(clock()-tstart)/CLOCKS_PER_SEC) << std::endl;
	}
	//RF.toString();
	return 0;
}
