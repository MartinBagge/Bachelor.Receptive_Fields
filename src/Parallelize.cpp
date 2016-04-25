/*
 * parallelize.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: martin
 */

#include "Parallelize.h"

Parallelize::Parallelize() {
	// TODO Auto-generated constructor stub

}

Parallelize::~Parallelize() {
	// TODO Auto-generated destructor stub
}


__global__ void d_createKernel(double *center, double *step, double *width, double *kernel, int size){
	int i = threadIdx.x;
	if(i < size)
		kernel[i] = exp((-(((center[i])-(step[i]))*((center[i])-(step[i])))/2)*(width[i]));
}

void Parallelize::d_createKernels(double *centers, double step, double width, double *kernelsArr, int centerSize, int kernelSize){
	//std::cout << "step" << step << std::endl;
	//std::cout << "width" << width << std::endl;
	  double stepArr[centerSize], widthArr[centerSize], *d_kernelCenter, *d_step, *d_kernelWidth, *d_kernel;


	  cudaMalloc((void**)&d_kernelCenter, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_step, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_kernelWidth, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_kernel, centerSize*sizeof(double));


	  for(int i = 0; i < centerSize; i++){
		  stepArr[i] = step;
		  widthArr[i] = width;
		  kernelsArr[i] = 0;
	  }

	  cudaMemcpy(d_kernelCenter, centers, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_step, stepArr, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernelWidth, widthArr, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernel, kernelsArr, centerSize*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_createKernel<<<1,centerSize>>>(d_kernelCenter, d_step, d_kernelWidth, d_kernel, centerSize);

	  cudaDeviceSynchronize();

	  cudaMemcpy(kernelsArr, d_kernel, centerSize*sizeof(double), cudaMemcpyDeviceToHost);

	  cudaFree(d_kernelCenter);
	  cudaFree(d_step);
	  cudaFree(d_kernelWidth);
	  cudaFree(d_kernel);


}

std::vector<double> Parallelize::createKernels(std::vector<double> centers, double step, double width, int size){
	double centersArr[centers.size()];
	std::copy(centers.begin(), centers.end(), centersArr);
	double kernelsArr[size];
	d_createKernels(centersArr, step, width, kernelsArr, centers.size(), size);
	std::vector<double> returnVector;
	for(int i = 0; i < size; i++){
		returnVector.push_back(kernelsArr[i]);
	}

	return returnVector;
}

__global__ void d_calcOutput(double *weights, double *kernels, double *output, int size){
	int i = threadIdx.x;
	if(i < size){
		output[i]= kernels[i]*weights[i];
	}
}

void Parallelize::calcOutput(double *weights, double *kernels, double *output, int centerSize){
	  double *d_weights, *d_output, *d_kernels;

	  cudaMalloc((void**)&d_kernels, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_weights, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_output, centerSize*sizeof(double));

	  cudaMemcpy(d_kernels, kernels, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_weights, weights, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_output, output, centerSize*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_calcOutput<<<1,centerSize>>>(d_weights, d_kernels, d_output, centerSize);

	  cudaDeviceSynchronize();

	  cudaMemcpy(output, d_output, centerSize*sizeof(double), cudaMemcpyDeviceToHost);

	  cudaFree(d_weights);
	  cudaFree(d_output);
	  cudaFree(d_kernels);
}

__global__ void d_updateWeights(double *learningRate, double *centers, double *target, double *output, double *weights, int size){
	int i = threadIdx.x;
	if(i < size){
		weights[i] = weights[i]+learningRate[i]*(target[llrint(centers[i])]-output[llrint(centers[i])]);
	}
}

void Parallelize::updateWeights(double learningRate, double *centers, double *target, double *output, double *weights, int size){
	  double learningRateArr[size], *d_centers, *d_target, *d_output, *d_weights, *d_learningRate;

	  cudaMalloc((void**)&d_centers, size*sizeof(double));
	  cudaMalloc((void**)&d_target, size*sizeof(double));
	  cudaMalloc((void**)&d_output, size*sizeof(double));
	  cudaMalloc((void**)&d_weights, size*sizeof(double));
	  cudaMalloc((void**)&d_learningRate, size*sizeof(double));

	  for(int i = 0; i < size; i++){
		  learningRateArr[i] = learningRate;
	  }

	  cudaMemcpy(d_centers, centers, size*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_target, target, size*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_output, output, size*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_weights, weights, size*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_learningRate, learningRateArr, size*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_updateWeights<<<1,size>>>(d_learningRate, d_centers, d_target, d_output, d_weights, size);

	  cudaDeviceSynchronize();

	  cudaMemcpy(weights, d_weights, size*sizeof(double), cudaMemcpyDeviceToHost);

	  cudaFree(d_centers);
	  cudaFree(d_target);
	  cudaFree(d_output);
	  cudaFree(d_weights);
	  cudaFree(d_learningRate);

}

std::vector<double> Parallelize::applyDeltaRule(double learningRate, std::vector<double> centers, std::vector<double> target, std::vector<double> weights, std::vector<double> kernels){
	std::vector<double> finalOutput(kernels[0]);
	double centersArr[centers.size()];
	std::copy(centers.begin(), centers.end(), centersArr);
	double targetArr[target.size()];
	std::copy(target.begin(), target.end(), targetArr);
	double weightsArr[weights.size()];
	std::copy(weights.begin(), weights.end(), weightsArr);

	double outputArr[target.size()];

	double kernelsArr[kernels.size()];
	for(int j = 0; j < target.size(); j++){
		for(int i = 0; i < centers.size(); i++){
			kernelsArr[i] = kernels[(i*kernels[0]+1+j)];
		}
		calcOutput(weightsArr, kernelsArr, outputArr, centers.size());
		for(int l = 0; l < centers.size(); l++){
				finalOutput[j]+=outputArr[l];
		}
	}
	updateWeights(learningRate, centersArr, targetArr, outputArr, weightsArr, centers.size());

	return finalOutput;
}
