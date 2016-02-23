/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"



ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double LearningRate, const int learningRateInterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth), learningRate(learningRate), learningRateIterations(learningRateIterations), targetSize(targetSize){
	gaussianKernels[numberOfKernels][targetSize];
	kernelCenters[numberOfKernels];
	alfa[targetSize];
	weights[numberOfKernels][1];
	targetPattern[targetSize];
	transKernels[targetSize][numberOfKernels];
	transWeights[1][numberOfKernels];
	transOutput[targetSize][1];
	output[1][targetSize];


	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters);
	linSpace(lowerLimit, upperLimit, targetSize, alfa);
	zeros(initialWeights);


}

void ReceptiveFields::createGaussianKernels(){
	for(int i = 0; i < numberOfKernels; i++){
		for(int j = 0; j < targetSize; j++){
			gaussianKernels[i][j] = exp(pow(-(double)(alfa[j]-kernelCenters[i]),2.0)/2*kernelWidth);
		}
	}
}

void ReceptiveFields::applyDeltaRule(){
	transposeMatrix(*gaussianKernels, *transKernels);
	for(int i = 0; i < learningRateIterations; i++){
		transposeMatrix(*weights, *transWeights);
		for(int j = 0; j < numberOfKernels; j++){
			for(int k = 0; k < targetSize; k++){
				transOutput[k][1] = transKernels[j][k]*transWeights[1][j];
			}
		}
		transposeMatrix(*transWeights, *weights);
		weights[i] = weights[i]+learningRate*(targetPattern[i]);
	}
	transposeMatrix(*transOutput, *output);
}

void ReceptiveFields::transposeMatrix(double *initialArray, double *returnArray){
	for(int i = 0; i < numberOfKernels; i++){
		for(int j = 0; j < targetSize; j++){
			returnArray[j][i] = initialArray[i][j];
		}
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

