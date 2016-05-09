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

ReceptiveFields createReceptiveFields(string inputName, int iterations, bool gpu, int &size){
	string token;
	vector<string> splitStrings;
	ifstream filein;
	filein.open(inputName.c_str());
	while(getline(filein, token, ',')){
		splitStrings.push_back(token);
	}
	ReceptiveFields RF(60, 120, 25, 1, 0.4, iterations, splitStrings.size(), gpu);
	size = splitStrings.size();
	for(int i = 0; i < splitStrings.size(); i++){
		RF.generateTarget(atof(splitStrings[i].c_str()));
	}

	return RF;

}

int main(){
	int iterations = 50000;
	bool gpu = true;
	//int kernels[]={20, 40, 60, 85};
	//int blocks[]={1, 5, 10, 50, 86, 100, 200};
	//for(int i = 0; i < sizeof(blocks)/sizeof(blocks[0]); i++){
		//for (int j = 0; j < sizeof(kernels)/sizeof(kernels[0]); j++){
			//std::cout/* << "blocks: " << blocks[i] */<< "     kernels: " << kernels[j] << std::endl;

	int size = 0;
	ReceptiveFields lefthip = createReceptiveFields("runbot_lefthip_cycle", iterations, gpu, size);
			//for (int i = 0; i < 10; i++){
				clock_t tstart = clock();
				int tmp = 1;
				for(int i = 0; i < size; i++){
					lefthip.createStep(tmp);
					tmp++;
				}
				lefthip.applyDeltaRule();
				std::cout << "Time: " << ((double)(clock()-tstart)/CLOCKS_PER_SEC) << std::endl;
			//}
		//}
	//}
	lefthip.toString();
	return 0;
}


