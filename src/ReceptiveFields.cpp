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
  weights1d(numberOfKernels), targetPattern1d(targetSize), output1d(targetSize){
	gaussianKernels2d[0] = targetSize;
	kernelCenters1d = linSpace(1, targetSize, numberOfKernels);
	weights1d = zeros(numberOfKernels);
	targetcount = 0;
	kernelCreationCounter = 0;

}

void ReceptiveFields::createStep(double step){
		for(int i = 0; i < numberOfKernels; i++){
			gaussianKernels2d[kernelCreationCounter+i*gaussianKernels2d[0]+1] = exp((-pow(((double)(kernelCenters1d[i]-step)),2)/2)*kernelWidth);
		}
		kernelCreationCounter++;
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

void ReceptiveFields::applyDeltaRule(){
	double value;
	for(int k = 0; k < learningIterations; k++){
		for(int i = 0; i < targetSize; i++){
			value = 0;
			for(int j = 0; j < numberOfKernels; j++){
				value += gaussianKernels2d[(j*gaussianKernels2d[0]+1+i)]*weights1d[j];
			}
			output1d[i]=value;
		}
		for(int l = 0; l < numberOfKernels; l++){
			weights1d[l] += learningRate*((double)targetPattern1d[round(kernelCenters1d[l])]-(double)output1d[round(kernelCenters1d[l])]);
		}
	}
}

std::vector<double> ReceptiveFields::linSpace(double start, double stop, double space){
	double addValue = (stop-start)/(space-1);
	double tmp = start;
	std::vector<double> returnVector(space);
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnVector[i] = start;
		}else{
			tmp += addValue;
			returnVector[i] = tmp;
		}
	}
	return returnVector;
}
