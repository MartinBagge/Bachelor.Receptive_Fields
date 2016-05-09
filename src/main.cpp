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
	ReceptiveFields RF(0, 0, 25, 2, 0.4, iterations, splitStrings.size(), gpu);
	size = splitStrings.size();
	for(int i = 0; i < splitStrings.size(); i++){
		RF.generateTarget(atof(splitStrings[i].c_str()));
	}
	return RF;

}

int main(){
	int iterations = 50000;
	bool gpu = true;
	int size_lefthip = 0;
	int size_righthip = 0;
	int size_leftknee = 0;
	int size_rightknee = 0;

	ReceptiveFields lefthip = createReceptiveFields("runbot_lefthip_cycle", iterations, gpu, size_lefthip);
	ReceptiveFields righthip = createReceptiveFields("runbot_righthip_cycle", iterations, gpu, size_righthip);
	ReceptiveFields leftknee = createReceptiveFields("runbot_leftknee_cycle", iterations, gpu, size_leftknee);
	ReceptiveFields rightknee = createReceptiveFields("runbot_rightknee_cycle", iterations, gpu, size_rightknee);

	int tmp_lefthip = 1;
	int tmp_righthip = 1;
	int tmp_leftknee = 1;
	int tmp_rightknee = 1;
	for(int i = 0; i < size_lefthip; i++){
		lefthip.createStep(tmp_lefthip);
		tmp_lefthip++;
	}
	for(int i = 0; i < size_righthip; i++){
		righthip.createStep(tmp_righthip);
		tmp_righthip++;
	}
	for(int i = 0; i < size_leftknee; i++){
		leftknee.createStep(tmp_leftknee);
		tmp_leftknee++;
	}
	for(int i = 0; i < size_rightknee; i++){
		rightknee.createStep(tmp_rightknee);
		tmp_rightknee++;
	}

	lefthip.applyDeltaRule();
	righthip.applyDeltaRule();
	leftknee.applyDeltaRule();
	rightknee.applyDeltaRule();

	lefthip.toString("lefthip_target-output.csv");
	righthip.toString("righthip_target-output.csv");
	leftknee.toString("leftknee_target-output.csv");
	rightknee.toString("rightknee_target-output.csv");

	return 0;
}


