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

	linSpace(lowerLimit, upperLimit, numberOfKernels, kernelCenters1d);
	//linSpace(lowerLimit, upperLimit, targetSize, alfa1d);
	zeros(weights1d);
	targetcount = 0;

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	for(int i = 0; i < numberOfKernels; i++){
		rowAdd = i*gaussianKernels2d[0]+1;
		for(int j = 0; j < gaussianKernels2d[0]; j++){
			gaussianKernels2d[j+rowAdd] = exp(pow(-((double)(alfa1d[j]-kernelCenters1d[i])),2)/2*kernelWidth);
		}
	}
	applyDeltaRule();
}

void ReceptiveFields::zeros(std::vector<double> returnArray){
	for(int i = 0; i < returnArray.size(); i++){
		returnArray[i] = 0;
	}
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
	transposeMatrix(gaussianKernels2d, transKernels2d, 2);
	int rowAdd;
	double value;
	for(int i = 0; i < learningIterations; i++){
		for(int j = 0; j < targetSize; j++){
			value = 0;
			rowAdd = j*transKernels2d[0]+1;
			for(int k = 0; k < numberOfKernels; k++){
				//no need for transKernels we can optimize and just use original Kernels instead
				std::cout << gaussianKernels2d[k+rowAdd] << std::endl;

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
