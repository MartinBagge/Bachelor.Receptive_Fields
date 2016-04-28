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
	bool gpu = false;
	int kernels[]={20, 40, 60, 85};
	int blocks[]={1, 5, 10, 50, 86, 100, 200};
	//for(int i = 0; i < sizeof(blocks)/sizeof(blocks[0]); i++){
		for (int j = 0; j < sizeof(kernels)/sizeof(kernels[0]); j++){
			std::cout/* << "blocks: " << blocks[i] */<< "     kernels: " << kernels[j] << std::endl;
			ReceptiveFields RF(60, 120, kernels[j], 0.1, 0.4, iterations, 85, gpu, 0);
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
			//for (int i = 0; i < 10; i++){
				clock_t tstart = clock();
				int tmp = 1;
				for(int i = 0; i < 85; i++){
					RF.createStep(tmp);
					tmp++;
				}
				RF.applyDeltaRule();
				std::cout << "Time: " << ((double)(clock()-tstart)/CLOCKS_PER_SEC) << std::endl;
			//}
		}
	//}
	//RF.toString();
	return 0;
}
