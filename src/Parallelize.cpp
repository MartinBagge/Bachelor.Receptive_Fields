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

__global__ void d_calcOutput(double *weights, double *kernels, double *output, int size, int loop, double *values){
	int i = threadIdx.x;
	if(i < size){
		for(int j = 0; j < loop; j++){
			if(j == 0){
				values[j] = kernels[((i*loop+1)*j)]*weights[i];
			}else{
				values[j] = values[j-1]+kernels[((i*loop+1)*j)]*weights[i];
			}
		}
		output[i]=values[loop-1];
	}
}

void Parallelize::calcOutput(double *weights, double *kernels, double *output, int centerSize, int targetSize, int kernelSize){
	  double values[targetSize], *d_values, *d_weights, *d_output, *d_kernels;

	  cudaMalloc((void**)&d_kernels, kernelSize*sizeof(double));
	  cudaMalloc((void**)&d_weights, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_output, targetSize*sizeof(double));
	  cudaMalloc((void**)&d_values, targetSize*sizeof(double));

	  cudaMemcpy(d_kernels, kernels, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_weights, weights, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_output, output, targetSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_values, values, targetSize*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_calcOutput<<<1,centerSize>>>(d_weights, d_kernels, d_output, centerSize, targetSize, d_values);

	  cudaDeviceSynchronize();

	  cudaMemcpy(output, d_output, targetSize*sizeof(double), cudaMemcpyDeviceToHost);

	  cudaFree(d_weights);
	  cudaFree(d_output);
	  cudaFree(d_kernels);
	  cudaFree(d_values);
}

__global__ void d_updateWeights(double *learningRate, double *centers, double *target, double *output, double *weights, int size){
	int i = threadIdx.x;
	if(i < size){
		weights[i] = weights[i]+learningRate[i]*(target[llrint(centers[i])]-output[llrint(centers[i])]);
	}
}

void Parallelize::updateWeights(double learningRate, double *centers, double *target, double *output, double *weights, int centerSize, int targetSize){
	  double learningRateArr[centerSize], *d_centers, *d_target, *d_output, *d_weights, *d_learningRate;

	  cudaMalloc((void**)&d_centers, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_target, targetSize*sizeof(double));
	  cudaMalloc((void**)&d_output, targetSize*sizeof(double));
	  cudaMalloc((void**)&d_weights, centerSize*sizeof(double));
	  cudaMalloc((void**)&d_learningRate, centerSize*sizeof(double));

	  for(int i = 0; i < centerSize; i++){
		  learningRateArr[i] = learningRate;
	  }

	  cudaMemcpy(d_centers, centers, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_target, target, targetSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_output, output, targetSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_weights, weights, centerSize*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_learningRate, learningRateArr, centerSize*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_updateWeights<<<1,centerSize>>>(d_learningRate, d_centers, d_target, d_output, d_weights, centerSize);

	  cudaDeviceSynchronize();

	  cudaMemcpy(weights, d_weights, centerSize*sizeof(double), cudaMemcpyDeviceToHost);

	  cudaFree(d_centers);
	  cudaFree(d_target);
	  cudaFree(d_output);
	  cudaFree(d_weights);
	  cudaFree(d_learningRate);

}

std::vector<double> Parallelize::applyDeltaRule(double learningRate, std::vector<double> centers, std::vector<double> target, std::vector<double> weights, std::vector<double> kernels, int learningIterations){
	std::vector<double> finalOutput(kernels[0]);
	double centersArr[centers.size()];
	std::copy(centers.begin(), centers.end(), centersArr);
	double targetArr[target.size()];
	std::copy(target.begin(), target.end(), targetArr);
	double weightsArr[weights.size()];
	std::copy(weights.begin(), weights.end(), weightsArr);
	double kernelsArr[kernels.size()];
	std::copy(kernels.begin(), kernels.end(), kernelsArr);

	double outputArr[target.size()];

	for(int i = 0; i < learningIterations; i++){
		calcOutput(weightsArr, kernelsArr, outputArr, centers.size(), target.size(), kernels.size());
		updateWeights(learningRate, centersArr, targetArr, outputArr, weightsArr, centers.size(), target.size());
	}

	return finalOutput;
}
