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
	std::vector<int> space = linSpaceInt(1, targetSize, numberOfKernels);
	for(int i = 0; i < numberOfKernels; i++){
		std::cout << space[i] << std::endl;
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
			weights1d[l] += learningRate*(targetPattern1d[space[l]]-output1d[space[l]]);
			if(k == 500){
				//std::cout << weights1d[l] << "," << targetPattern1d[l] << "," << alfa1d[l] << std::endl;
			}
		}
	}

}

//might not be needed as inputs are preffered
std::vector<double> ReceptiveFields::linSpaceDouble(int start, int stop, int space){
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
	}

	std::cout << "output" << std::endl;
	for(int i = 0; i < targetSize; i++){
		//std::cout << i << "," << output1d[i] << "," << targetPattern1d[i] << std::endl;
		//std::cout << gaussianKernels2d[i+1+100*gaussianKernels2d[0]] << std::endl;
		//std::cout << alfa1d[i] << std::endl;
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
