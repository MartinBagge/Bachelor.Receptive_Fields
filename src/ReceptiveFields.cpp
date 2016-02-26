/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"



ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize)
: lowerLimit(lowerLimit), upperLimit(upperLimit), numberOfKernels(numberOfKernels), kernelWidth(kernelWidth), learningRate(learningRate), learningIterations(learningIterations), targetSize(targetSize),
  gaussianKernels2d(numberOfKernels*targetSize+1), kernelCenters1d(numberOfKernels), alfa1d(targetSize), weights1d(numberOfKernels), targetPattern1d(targetSize), transKernels2d(targetSize*numberOfKernels+1),
  /*transWeights1d(numberOfKernels), transOutput1d(targetSize), */output1d(targetSize){
/*
	gaussianKernels(boost::extents[numberOfKernels][targetSize]);
	kernelCenters(boost::extents[numberOfKernels]);
	alfa(boost::extents[targetSize]);
	weights(boost::extents[numberOfKernels][1]);
	targetPattern(boost::extents[targetSize]);
	transKernels(boost::extents[targetSize][numberOfKernels]);
	transWeights(boost::extents[1][numberOfKernels]);
	transOutput(boost::extents[targetSize][1]);
	output(boost::extents[1][targetSize]);
*/
	gaussianKernels2d[0] = numberOfKernels;
	transKernels2d[0] = targetSize;

	genTargetPattern(targetPattern1d);

	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters1d);
	linSpace(lowerLimit, upperLimit, targetSize, alfa1d);
	zeros(weights1d);

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	for(int i = 0; i < targetSize; i++){
		rowAdd = i*gaussianKernels2d[0]+1;
		for(int j = 0; j < gaussianKernels2d[0]; j++){
			gaussianKernels2d[j+rowAdd] = exp(pow(-(double)(alfa1d[i]-kernelCenters1d[j]),2.0)/2*kernelWidth);
		}
	}
}

void ReceptiveFields::applyDeltaRule(){
	transposeMatrix(gaussianKernels2d, transKernels2d, 2);
	int rowAdd;
	for(int i = 0; i < learningIterations; i++){
		for(int j = 0; j < numberOfKernels; j++){
			for(int k = 0; k < targetSize; k++){
				output1d[k] = transKernels2d[j*k]*weights1d[j];
			}
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
				rowAdd = i*returnArray[0];
				for(int j = 0; j < returnArray[0]; j++){
					returnArray[1+j+rowAdd] = initialArray[1+i+j*initialArray[0]];
				}
			}
		break;
	default:
		std::cout << "Dimension not supported" << std::endl;
	}

}

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
		returnArray[i][1] = 0;
	}
}

void ReceptiveFields::genTargetPattern(std::vector<double> returnArray){
	int value = 0;
	for(int i = 0; i < returnArray.size(); i++){
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

