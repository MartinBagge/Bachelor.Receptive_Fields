/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"



ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels,
		const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth),
  learningRate(learningRate), learningIterations(learningIterations), targetSize(targetSize),
  gaussianKernels2d(numberOfKernels*targetSize+1), kernelCenters1d(numberOfKernels), alfa1d(targetSize),
  weights1d(numberOfKernels), targetPattern1d(targetSize), transKernels2d(targetSize*numberOfKernels+1), output1d(targetSize){
	std::cout << "ReceptiveFields" << std::endl;
	gaussianKernels2d[0] = targetSize;
	kernelCenters1d = linSpaceDouble(1, targetSize, numberOfKernels);
	weights1d = zeros(numberOfKernels);
	targetcount = 0;

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	std::cout << "gaussian" << std::endl;
	for(int i = 0; i < numberOfKernels; i++){
		rowAdd = i*gaussianKernels2d[0]+1;
		for(int j = 0; j < gaussianKernels2d[0]; j++){
			gaussianKernels2d[j+rowAdd] = exp(-pow(((double)(alfa1d[j]-kernelCenters1d[i])),2)/(2*kernelWidth));
			//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
		}
	}
	for(int k = 1; k < 267; k++){
		//std::cout << gaussianKernels2d[k+(266*50)] << std::endl;

	}
	applyDeltaRule();
}

std::vector<double> ReceptiveFields::zeros(int size){
	std::vector<double> returnVector(size);
	for(int i = 0; i < size; i++){
		returnVector[i] = 0;
	}
	return returnVector;
}

ReceptiveFields::~ReceptiveFields() {
	// TODO Auto-generated destructor stub
}


//LEARNING
void ReceptiveFields::generateTarget(double input){
	targetPattern1d[targetcount]=input;
	targetcount++;
}

void ReceptiveFields::generateAlfaPattern(){
	for(int i = 0; i<targetSize; i++){
		alfa1d[i]=i+1;
	}
}

void ReceptiveFields::applyDeltaRule(){
	double value;
	std::cout << "delta rule" << std::endl;
	std::vector<double> space = linSpaceDouble(1, targetSize, numberOfKernels);
	for(int i = 0; i < numberOfKernels; i++){
		//std::cout << round(space[i]) << std::endl;
	}
	for(int k = 0; k < learningIterations; k++){
		for(int i = 0; i < targetSize; i++){
			value = 0;
			for(int j = 0; j < numberOfKernels; j++){
				value += gaussianKernels2d[j*gaussianKernels2d[0]+1+i]*weights1d[j];
			}
			if(k==500){

				//std::cout << gaussianKernels2d[10*gaussianKernels2d[0]+1+i] << std::endl;
			}

			output1d[i]=value;
		}
		for(int l = 0; l < numberOfKernels; l++){
			weights1d[l] += learningRate*(targetPattern1d[round(space[l])]-output1d[round(space[l])]);
			//weights1d[l] += learningRate*(targetPattern1d[l]-output1d[l]);
			if(k == 500){
				//std::cout << weights1d[l] << "," << targetPattern1d[l] << "," << alfa1d[l] << std::endl;
			}
		}
	}
	for(int i = 0; i < targetSize; i++){
		//std::cout << output1d[i] << std::endl;
	}
	for(int l = 0; l < numberOfKernels; l++){
		//std::cout << weights1d[l] << std::endl;
	}

}

//might not be needed as inputs are preffered
std::vector<double> ReceptiveFields::linSpaceDouble(int start, int stop, int space){
	double addValue = (stop-start)/(double)space;
	double tmp = 0;
	std::vector<double> returnVector(space);
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnVector[i] = start;
		}else{
			tmp += addValue;
			returnVector[i] = tmp;
			//std::cout << returnVector[i] << std::endl;
		}
	}
	return returnVector;
}

std::vector<int> ReceptiveFields::linSpaceInt(int start, int stop, int space){
	double addValue = (stop-start)/space;
	std::cout << addValue << std::endl;
	std::vector<int> returnVector(space);
	double tmp = start;
	for(int i = 0; i < space; i++){
		tmp +=addValue;
		returnVector[i] = round(tmp);
		//std::cout << returnVector[i] << std::endl;
	}
	return returnVector;
}


//prob not needed
void ReceptiveFields::genTargetPattern(double (func)(int)){
	for(int i = 0; i < targetPattern1d.size(); i++){
		double d = func(i);
		targetPattern1d[i] = d;
	}
}

void ReceptiveFields::toString(){
	std::cout << "weights" << std::endl;
	for (int i = 0; i < numberOfKernels; i++){
		//std::cout << weights1d[i] << std::endl;
		//std::cout << gaussianKernels2d[200+1+i*gaussianKernels2d[0]] << std::endl;
	}

	std::cout << "output" << std::endl;
	for(int i = 0; i < targetSize; i++){
		std::cout << i << "," << output1d[i] << "," << targetPattern1d[i] << std::endl;
		//std::cout << alfa1d[i] << std::endl;
	}

	// Gaussian kernels write file
	std::ofstream fileKernels;
	fileKernels.open("datasetKernels.csv");
	int rowAdd;
	for(int i = 0; i < numberOfKernels; i++){
			rowAdd = i*gaussianKernels2d[0]+1;
			for(int j = 0; j < gaussianKernels2d[0]; j++){

				if(j == gaussianKernels2d[0]-1){
					fileKernels << gaussianKernels2d[j+rowAdd];
				}else{
					fileKernels << gaussianKernels2d[j+rowAdd] << ",";
				}
				//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
			}
			fileKernels << "\n";
		}
	fileKernels.close();
	/*
	std::ofstream file;
	file.open("dataset.csv");
	for (int i = 0; i < targetSize; i++){
		file << i << "," << output1d[i] << "," << targetPattern1d[i] << "\n";
	}

	file.close();
	/*
	std::cout << "Lower Limit: ";
	std::cout << lowerLimit << std::endl;
	std::cout << "Upper Limit: ";
	std::cout << upperLimit << std::endl;

	std::cout << "Number of Kernels: ";
	std::cout << numberOfKernels << std::endl;
	std::cout << "Kernel Width: ";
	std::cout << kernelWidth << std::endl;
	*/

}
