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
  	//TODO: delete cout
	std::cout << "ReceptiveFields" << std::endl;
	gaussianKernels2d[0] = targetSize;
	kernelCenters1d = linSpace(1, targetSize, numberOfKernels);
	weights1d = zeros(numberOfKernels);
	targetcount = 0;
	kernelCreationCounter = 0;

}

void ReceptiveFields::createGaussianKernels(){
	int rowAdd;
	//TODO: delete cout
	std::cout << "gaussian" << std::endl;
	for(int i = 0; i < gaussianKernels2d[0]; i++){
		for(int j = 0; j < numberOfKernels; j++){
			gaussianKernels2d[i+j*gaussianKernels2d[0]+1] = exp(-pow(kernelCenters1d[j]-alfa1d[i],2)/(2*kernelWidth));
			//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
			  if (i == 21){
			    std::cout << ". " << std::endl;
			    std::cout << "a, center-alfa²: " << pow(kernelCenters1d[j]-alfa1d[i],2) << std::endl;
			    std::cout << "b, 2*width: " << 2*kernelWidth << std::endl;
			    std::cout << "c, a/b: " << pow(kernelCenters1d[j]-alfa1d[i],2)/(2*kernelWidth) << std::endl;
			    std::cout << "d, -c: " << -(pow(kernelCenters1d[j]-alfa1d[i],2))/(2*kernelWidth) << std::endl;
			    std::cout << "e, exp(d): " << exp(-(pow(kernelCenters1d[j]-alfa1d[i],2))/(2*kernelWidth)) << std::endl;
			    std::cout << ". " << std::endl;
			   }
		}
	}
	applyDeltaRule();
}

void ReceptiveFields::createStep(double step){

	//TODO: check for rewrite correctness
		std::cout << "gaussian" << std::endl;
		for(int i = 0; i < numberOfKernels; i++){
			gaussianKernels2d[kernelCreationCounter+i*gaussianKernels2d[0]+1] = exp(-pow(((double)(kernelCenters1d[i]-step)),2)/(2*kernelWidth));
			//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
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

void ReceptiveFields::generateAlfaPattern(){
	for(int i = 0; i<targetSize; i++){
		alfa1d[i]=i+1;
	}
}

void ReceptiveFields::applyDeltaRule(){
	double value;
	//TODO: delete cout
	std::cout << "delta rule" << std::endl;
	std::vector<double> space = linSpace(1, targetSize, numberOfKernels);
	//TODO: delete test loop
	for(int i = 0; i < numberOfKernels; i++){
		//std::cout << round(space[i]) << std::endl;
	}
	for(int k = 0; k < learningIterations; k++){
		for(int i = 0; i < targetSize; i++){
			value = 0;
			for(int j = 0; j < numberOfKernels; j++){
				value += gaussianKernels2d[j*gaussianKernels2d[0]+1+i]*weights1d[j];
			}
			//TODO: delete test cout
			if(k==500){

				//std::cout << gaussianKernels2d[10*gaussianKernels2d[0]+1+i] << std::endl;
			}

			output1d[i]=value;
		}
		for(int l = 0; l < numberOfKernels; l++){
			//two different approches first one is prefferable
			weights1d[l] = weights1d[l]+(learningRate*((double)targetPattern1d[round(space[l])]-(double)output1d[round(space[l])]));
			//weights1d[l] += learningRate*(targetPattern1d[l]-output1d[l]);
			//TODO: delete test cout
			if(k == 500){
				//std::cout << weights1d[l] << "," << targetPattern1d[l] << "," << alfa1d[l] << std::endl;
			}
		}
	}
	//TODO: delete both test couts
	for(int i = 0; i < targetSize; i++){
		//std::cout << output1d[i] << std::endl;
	}
	for(int l = 0; l < numberOfKernels; l++){
		//std::cout << weights1d[l] << std::endl;
	}

}

//might not be needed as inputs are preffered
std::vector<double> ReceptiveFields::linSpace(int start, int stop, int space){
	double addValue = (stop-start)/(double)space;
	double tmp = 0;
	std::vector<double> returnVector(space);
	for(int i = 0; i < space; i++){
		if(i == 0){
			returnVector[i] = start;
		}else{
			tmp += addValue;
			returnVector[i] = tmp;
			//TODO: delete cout
			//std::cout << returnVector[i] << std::endl;
		}
	}
	return returnVector;
}

//method is mainly for testing purposes and should probably be deleted upon delievering the framework
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
	for(int i = 0; i < numberOfKernels; i++){
			for(int j = 0; j < targetSize; j++){

				if(j == gaussianKernels2d[0]-1){
					fileKernels << gaussianKernels2d[i*gaussianKernels2d[0]+1+j];
				}else{
					fileKernels << gaussianKernels2d[i*gaussianKernels2d[0]+1+j] << ",";
				}
				//std::cout << alfa1d[j] << " , " << kernelCenters1d[i] << std::endl;
			}
			fileKernels << "\n";
		}
	fileKernels.close();

}
