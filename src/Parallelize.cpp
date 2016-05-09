/*
 * parallelize.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: martin
 */

#include "Parallelize.h"

Parallelize::Parallelize() {

}

Parallelize::~Parallelize() {
	// TODO Auto-generated destructor stub
}

//GENEREL KERNEL CREATION
//kernel function runs on gpu
__global__ void d_createKernel(float *center, float step, float width, float *kernel, int size){

	int i = threadIdx.x + blockIdx.x * blockDim.x;
		//printf("kernel, threadI %d, blockid %d, blockdim %d\n", threadIdx.x, blockIdx.x, blockDim.x);
	if(i < size)
		kernel[i] = exp((-(((center[i])-(step))*((center[i])-(step))))/(2*(width*width)));
}

//prepare function(runs on CPU prepares GPU)
void Parallelize::d_createKernels(float *centers, float step, float width, float *kernelsArr, int centerSize, int kernelSize, int numberOfBlocks){
	//std::cout << "step" << step << std::endl;
	//std::cout << "width" << width << std::endl;
	float *d_kernelCenter,*d_kernel;


	  cudaMalloc((void**)&d_kernelCenter, centerSize*sizeof(float));
	  cudaMalloc((void**)&d_kernel, centerSize*sizeof(float));

	  for(int i = 0; i < centerSize; i++){
		  kernelsArr[i] = 0;
	  }

	  cudaMemcpy(d_kernelCenter, centers, centerSize*sizeof(float), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernel, kernelsArr, centerSize*sizeof(float), cudaMemcpyHostToDevice);

	  //function call
	  d_createKernel<<<numberOfBlocks,((int)(centerSize/numberOfBlocks))+1>>>(d_kernelCenter, step, width, d_kernel, centerSize);
	  //d_createKernel<<<1, 20>>>(d_kernelCenter, step, width, d_kernel, centerSize);
	  cudaDeviceSynchronize();

	  cudaMemcpy(kernelsArr, d_kernel, centerSize*sizeof(float), cudaMemcpyDeviceToHost);

	  cudaFree(d_kernelCenter);
	  cudaFree(d_kernel);



}

//Public method to be called from outside
std::vector<double> Parallelize::createKernels(std::vector<double> centers, double step, double width, int size, int numberOfBlocks){
	float centersArr[centers.size()];
	for(int i = 0; i < centers.size(); i++){
			centersArr[i] = (float)centers[i];
		}
	//std::copy(centers.begin(), centers.end(), centersArr);
	float kernelsArr[size];
	d_createKernels(centersArr, step, width, kernelsArr, centers.size(), size, numberOfBlocks);
	std::vector<double> returnVector;
	for(int i = 0; i < size; i++){
		returnVector.push_back(kernelsArr[i]);
	}

	return returnVector;
}

//SIMPLE LEARNING

//kernel functions

__global__ void d_calcOutput(float *weights, float *kernels, float *output, int centerSize, int targetSize){
	int i = threadIdx.x + blockIdx.x * blockDim.x;
			//printf("output, threadI %d, blockid %d, blockdim %d\n", threadIdx.x, blockIdx.x, blockDim.x);
	if(i < targetSize){
		float value = 0;
		for(int j = 0; j < centerSize; j++){
			value = value+kernels[(j*targetSize+1+i)]*weights[j];
		}
		output[i]=value;
	}
}

__global__ void d_updateWeights(float learningRate, float *centers, float *target, float *output, float *weights, int size){
	int i = threadIdx.x + blockIdx.x * blockDim.x;
		//printf("weight, threadI %d, blockid %d, blockdim %d, size %d \n", threadIdx.x, blockIdx.x, blockDim.x, size);
	if(i < size){
		weights[i] = weights[i]+(learningRate*((float)target[lround(centers[i])]-(float)output[lround(centers[i])]));
	}
}


//prepare function
void d_deltarule(float learningRate, float *centers, float *target, float *output, float *weights, float *kernels, int centerSize, int targetSize, int kernelSize, int iterations, int numberOfBlocks){
	float *d_centers, *d_target, *d_output, *d_weights, *d_kernels;

	//std::cout << learningRate << "     " << targetSize << "     " << centerSize << "     " << kernelSize<< "     " << iterations << std::endl;

	cudaMalloc((void**)&d_centers, centerSize*sizeof(float));
	cudaMalloc((void**)&d_target, targetSize*sizeof(float));
	cudaMalloc((void**)&d_output, targetSize*sizeof(float));
	cudaMalloc((void**)&d_weights, centerSize*sizeof(float));
	cudaMalloc((void**)&d_kernels, kernelSize*sizeof(float));

	cudaMemcpy(d_centers, centers, centerSize*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_target, target, targetSize*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_output, output, targetSize*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_weights, weights, centerSize*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_kernels, kernels, kernelSize*sizeof(float), cudaMemcpyHostToDevice);
	//std::cout << "before iterations:" << iterations << std::endl;
	for(int i = 0; i < iterations; i++){
		//std::cout << "in iteration: " << i << std::endl;
		d_calcOutput<<<numberOfBlocks,((int)(targetSize/numberOfBlocks))+1>>>(d_weights, d_kernels, d_output, centerSize, targetSize);
		//d_calcOutput<<<1, 85>>>(d_weights, d_kernels, d_output, centerSize, targetSize);
		cudaDeviceSynchronize();

		if(i != iterations-1){

			d_updateWeights<<<numberOfBlocks,((int)(centerSize/numberOfBlocks))+1>>>(learningRate, d_centers, d_target, d_output, d_weights, centerSize);
			//d_updateWeights<<<1, 20>>>(learningRate, d_centers, d_target, d_output, d_weights, centerSize);
			cudaDeviceSynchronize();

		}
	}
	std::cout << "after iterations" << std::endl;
	cudaMemcpy(output, d_output, targetSize*sizeof(float), cudaMemcpyDeviceToHost);

	cudaFree(d_centers);
	cudaFree(d_target);
	cudaFree(d_output);
	cudaFree(d_weights);
	cudaFree(d_kernels);

}

//public function to apply learning
std::vector<double> Parallelize::applyDeltaRule(float learningRate, std::vector<double> centers, std::vector<double> target, std::vector<double> weights, std::vector<double> kernels, int learningIterations, int numberOfBlocks){
	float centersArr[centers.size()];
	for(int i = 0; i < centers.size(); i++){
		centersArr[i] = (float)centers[i];
	}
	//std::copy(centers.begin(), centers.end(), centersArr);

	float targetArr[target.size()];
	for(int i = 0; i < target.size(); i++){
			targetArr[i] = (float)target[i];
		}
	//std::copy(target.begin(), target.end(), targetArr);

	float weightsArr[weights.size()];
	for(int i = 0; i < weights.size(); i++){
			weightsArr[i] = (float)weights[i];
		}
	//std::copy(weights.begin(), weights.end(), weightsArr);

	float kernelsArr[kernels.size()];
	for(int i = 0; i < kernels.size(); i++){
			kernelsArr[i] = (float)kernels[i];
		}
	//std::copy(kernels.begin(), kernels.end(), kernelsArr);

	float outputArr[target.size()];

	for(int i = 0; i < target.size(); i++){
		outputArr[i] = 0;
	}

	d_deltarule(learningRate, centersArr, targetArr, outputArr, weightsArr, kernelsArr, centers.size(), target.size(), kernels.size(), learningIterations, numberOfBlocks);

	std::vector<double> finalOutput(outputArr, outputArr+target.size());

	return finalOutput;
}
