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
	int iterations = 50000;
	bool gpu = true;
	int targetSize = 85;
			ReceptiveFields RF(60, 120, 20, 4, 0.4, iterations, targetSize, gpu);
			string inputString;
			string token;
			vector<string> splitStrings;
			ifstream filein;
			filein.open("runbot_leftknee_output.log");
			/*
			while(getline(filein,inputString)){
			 		stringstream lineStream(inputString);
			 		splitStrings.clear();
			 		while(getline(lineStream, token, ',')){
			 			splitStrings.push_back(token);
			 		}
			 		RF.generateTarget(atof(splitStrings[8].c_str()));
			 	}*/
			while(getline(filein, token, ',')){
				splitStrings.push_back(token);
			}
			for(int i = 0; i < splitStrings.size(); i++){
				RF.generateTarget(atof(splitStrings[i].c_str()));
			}
				clock_t tstart = clock();
				int tmp = 1;
				for(int i = 0; i < targetSize; i++){
					RF.createStep(tmp);
					tmp++;
				}
				RF.applyDeltaRule();
				double time = ((double)(clock()-tstart)/CLOCKS_PER_SEC);

				RF.toString();
				std::cout << "Time: " << time << std::endl;

	return 0;
}
