/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"



ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth), learningRate(learningRate), learningIterations(learningIterations), targetSize(targetSize){

	gaussianKernels(boost::extents[numberOfKernels][targetSize]);
	kernelCenters(boost::extents[numberOfKernels]);
	alfa(boost::extents[targetSize]);
	weights(boost::extents[numberOfKernels][1]);
	targetPattern(boost::extents[targetSize]);
	transKernels(boost::extents[targetSize][numberOfKernels]);
	transWeights(boost::extents[1][numberOfKernels]);
	transOutput(boost::extents[targetSize][1]);
	output(boost::extents[1][targetSize]);

	genTargetPattern(targetPattern);

	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters);
	linSpace(lowerLimit, upperLimit, targetSize, alfa);
	zeros(weights);

}

void ReceptiveFields::createGaussianKernels(){
	for(int i = 0; i < numberOfKernels; i++){
		for(int j = 0; j < targetSize; j++){
			gaussianKernels[i][j] = exp(pow(-(double)(alfa[j]-kernelCenters[i]),2.0)/2*kernelWidth);
		}
	}
}

void ReceptiveFields::applyDeltaRule(){
	transposeMatrix(gaussianKernels, transKernels);
	for(int i = 0; i < learningIterations; i++){
		transposeMatrix(weights, transWeights);
		for(int j = 0; j < numberOfKernels; j++){
			for(int k = 0; k < targetSize; k++){
				transOutput[k][1] = transKernels[j][k]*transWeights[1][j];
			}
		}
		transposeMatrix(transOutput, output);
		for(int l = 0; l < numberOfKernels; l++){
			weights[l][1] = weights[l][1]+learningRate*(targetPattern[l]-output[1][l]);
		}

	}

}

void ReceptiveFields::transposeMatrix(twoDimArray initialArray, twoDimArray returnArray){
	for(int i = 0; i < numberOfKernels; i++){
		for(int j = 0; j < targetSize; j++){
			returnArray[j][i] = initialArray[i][j];
		}
	}
}

void ReceptiveFields::linSpace(int start, int stop, int space, oneDimArray returnArray){
	double addValue = (stop-start)/space;
	for(int i = 0; i < space; i++){
		if(i == 0){
			std::cout << "returnArray size: " << returnArray.dimensionality << std::endl;
			returnArray[i] = start;
		}else{
			returnArray[i] = returnArray[i-1]+addValue;
		}
	}
}

void ReceptiveFields::zeros(twoDimArray returnArray){
	for(int i = 0; i < returnArray.shape()[0]; i++){
		returnArray[i][1] = 0;
	}
}

void ReceptiveFields::genTargetPattern(oneDimArray returnArray){
	int value = 0;
	for(int i = 0; i < returnArray.shape()[0]; i++){
		returnArray[i] = value*2*M_PI;
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

