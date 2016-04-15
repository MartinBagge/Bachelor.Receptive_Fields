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

	gaussianKernels2d[0] = targetSize;
	transKernels2d[0] = numberOfKernels;
	kernelCenters1d = linSpace(1, targetSize, numberOfKernels);
	weights1d = zeros(numberOfKernels);
	targetcount = 0;

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	for(int i = 0; i < numberOfKernels; i++){
		rowAdd = i*gaussianKernels2d[0]+1;
		for(int j = 0; j < gaussianKernels2d[0]; j++){
			gaussianKernels2d[j+rowAdd] = exp(pow(-((double)(alfa1d[j]-kernelCenters1d[i])),2)/2*kernelWidth);
			//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
		}
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
	/*for(int i=0; i < gaussianKernels2d.size(); i++){
			std::cout << "gaussianKernels2d" << std::endl;
			std::cout << gaussianKernels2d[i] << std::endl;
		}*/
	transKernels2d = transposeMatrix(gaussianKernels2d, gaussianKernels2d.size(), 2);
	for(int i=0; i < transKernels2d.size(); i++){
				std::cout << "transKernels2d" << std::endl;
				std::cout << transKernels2d[i] << std::endl;
			}
	int rowAdd;
	double value;
	for(int i = 0; i < learningIterations; i++){
		for(int j = 0; j < targetSize; j++){
			value = 0;
			rowAdd = j*transKernels2d[0]+1;
			for(int k = 0; k < numberOfKernels; k++){
				//no need for transKernels we can optimize and just use original Kernels instead
				//std::cout << gaussianKernels2d[k+rowAdd] << std::endl;

				//std::cout << weights1d[k] << std::endl;
				value += transKernels2d[k+rowAdd]*weights1d[k];
				output1d[j]=value;
				for(int l = 0; l < numberOfKernels; l++){
					weights1d[l] = weights1d[l]+learningRate*(targetPattern1d[l]-alfa1d[l]);
				}
			}
		}
	}

}

std::vector<double> ReceptiveFields::transposeMatrix(std::vector<double> initialArray, int size, int numberOfDims){
	std::vector<double> returnVector(size);
	switch(numberOfDims){
	case 2:
		returnVector[0]=initialArray[0];
		int rowAdd;
		for(int i = 0; i < initialArray[0]; i++){
			rowAdd = i*returnVector[0]+1;
			for(int j = 0; j < returnVector[0]; j++){
				returnVector[j+rowAdd] = initialArray[1+i+j*initialArray[0]];
			}
		}
		return returnVector;
	default:
		std::cout << "Dimension not supported" << std::endl;
	}

}
//might not be needed as inputs are preffered
std::vector<double> ReceptiveFields::linSpace(int start, int stop, int space){
	double addValue = (stop-start)/space;
	std::cout << addValue << std::endl;
	std::vector<double> returnVector(space);
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnVector[i] = start;
		}else{
			returnVector[i] = returnVector[(i-1)]+addValue;
			//std::cout << returnVector[i] << std::endl;
		}
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

	for(int i = 0; i < output1d.size(); i++){
		std::cout << output1d[i] << std::endl;
	}
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
