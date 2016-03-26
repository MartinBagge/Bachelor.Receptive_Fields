/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"



ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth), learningRate(learningRate), learningIterations(learningIterations), targetSize(targetSize), gaussianKernels2d(numberOfKernels*targetSize+1), kernelCenters1d(numberOfKernels), alfa1d(targetSize), weights1d(numberOfKernels), targetPattern1d(targetSize), transKernels2d(targetSize*numberOfKernels+1), output1d(targetSize){

	gaussianKernels2d[0] = targetSize;
	transKernels2d[0] = numberOfKernels;

	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters1d);
	linSpace(lowerLimit, upperLimit, targetSize, alfa1d);
	zeros(weights1d);
	createGaussianKernels();

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	for(int i = 0; i < numberOfKernels; i++){
		rowAdd = i*gaussianKernels2d[0]+1;
		for(int j = 0; j < gaussianKernels2d[0]; j++){
			gaussianKernels2d[j+rowAdd] = exp(pow(-(double)(alfa1d[j]-kernelCenters1d[i]),2.0)/2*kernelWidth);
		}
	}
}

void ReceptiveFields::applyDeltaRule(){
	transposeMatrix(gaussianKernels2d, transKernels2d, 2);
	int rowAdd;
	double value;
	for(int i = 0; i < learningIterations; i++){
		for(int j = 0; j < targetSize; j++){
			value = 0;
			rowAdd = j*transKernels2d[0]+1;
			for(int k = 0; k < numberOfKernels; k++){
				//no need for transKernels we can optimize and just use Kernels instead
				value += transKernels2d[k+rowAdd]*weights1d[k];
			}
			output1d[j]=value;
		}
		for(int l = 0; l < numberOfKernels; l++){
			weights1d[l] = weights1d[l]+learningRate*(targetPattern1d[l]-output1d[l]);
		}

	}

}

void ReceptiveFields::transposeMatrix(std::vector<double> initialArray, std::vector<double> returnArray, int numberOfDims){
	switch(numberOfDims){
	case 2:
		int rowAdd;
			for(int i = 0; i < initialArray[0]; i++){
				rowAdd = i*returnArray[0]+1;
				for(int j = 0; j < returnArray[0]; j++){
					returnArray[j+rowAdd] = initialArray[1+i+j*initialArray[0]];
				}
			}
		break;
	default:
		std::cout << "Dimension not supported" << std::endl;
	}

}
//might not be needed as inputs are preffered
void ReceptiveFields::linSpace(int start, int stop, int space, std::vector<double> returnArray){
	double addValue = (stop-start)/space;
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnArray[i] = start;
		}else{
			returnArray[i] = returnArray[i-1]+addValue;
		}
	}
}

void ReceptiveFields::zeros(std::vector<double> returnArray){
	for(int i = 0; i < returnArray.size(); i++){
		returnArray[i] = 0;
	}
}

void ReceptiveFields::genTargetPattern(double (func)(int)){
	int value = 0;
	for(int i = 0; i < targetPattern1d.size(); i++){
		double d = func(i);
		targetPattern1d[i] = value*d;
		value += 1/targetSize;
	}
}

ReceptiveFields::~ReceptiveFields() {
	// TODO Auto-generated destructor stub
}

void ReceptiveFields::toString(){
	std::cout << "Lower Limit: ";
	std::cout << lowerLimit << std::endl;
	std::cout << "Upper Limit: ";
	std::cout << upperLimit << std::endl;

	std::cout << "Number of Kernels: ";
	std::cout << numberOfKernels << std::endl;
	std::cout << "Kernel Width: ";
	std::cout << kernelWidth << std::endl;

}
