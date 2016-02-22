/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"


ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double LearningRate, const int learningRateInterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth), learningRate(learningRate), learningRateIterations(learningRateIterations), targetSize(targetSize){
	gaussianKernels[numberOfKernels];
	kernelCenters[numberOfKernels];
	alfa[targetSize];
	weights[numberOfKernels];
	targetPattern[targetSize];


	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters);
	linSpace(lowerLimit, upperLimit, targetSize, alfa);
	zeros(initialWeights);


}

void ReceptiveFields::createGaussianKernels(){
	for(int i = 0; i < numberOfKernels; i++){
		gaussianKernels[i] = exp(-(alfa-kernelCenters[i]))²/2*kernelWidth;
	}
}

void ReceptiveFields::applyDeltaRule(){
	for(int i = 0; i < learningRateIterations; i++){
		weights[i] = weights[i]+learningRate*(targetPattern[i])
	}
}

void ReceptiveFields::linSpace(int start, int stop, int space, double *returnArray){
	double addValue = (stop-start)/space;
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnArray[i] = start;
		}else{
			returnArray[i] = returnArray[i-1]+addValue;
		}
	}
}

void ReceptiveFields::zeros(double *returnArray){
	for(int i = 0; i < sizeof(returnArray); i++){
		returnArray[i] = 0;
	}
}

void ReceptiveFields::targetPattern(double *returnArray){
	int value = 0;
	for(int i = 0; i < sizeof(returnArray); i++){
		returnArray[i] = value*2*M_PI;
		value += 1/targetSize;
	}
}

ReceptiveFields::~ReceptiveFields() {
	// TODO Auto-generated destructor stub
}

