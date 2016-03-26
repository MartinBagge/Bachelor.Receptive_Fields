#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ReceptiveFields.h"
using namespace std;

int main(){
	cout << "Test" << endl;

	ReceptiveFields* RF = new ReceptiveFields(45, 180, 20, 0.025, 0.2, 100, 1000);
	RF->toString();
	cout << "lala";
	//Read data file
	vector<string> inputStrings;
	ifstream filein;
	filein.open("filename.extension");
	int index = 0;
	while(!filein.eof()){
		getline(filein,inputStrings[index]);
		index++;
	}
	vector<string> splitStrings;
	string delimiter = " ";
	string token;
	size_t pos = 0;
	for(int i = 0; i < inputStrings.size(); i++){
		while((pos = inputStrings[i].find(delimiter)) != std::string::npos){
			token = inputStrings[i].substr(0,pos);
			splitStrings.push_back(token);
			inputStrings[i].erase(0, pos + delimiter.length());	
		}
		//call receptive fields
	}
	filein.close();
	return 0;
}
