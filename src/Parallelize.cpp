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

	  cudaMemcpy(centers, d_kernelCenter, centerSize*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(stepArr, d_step, centerSize*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(widthArr, d_kernelWidth, centerSize*sizeof(double), cudaMemcpyDeviceToHost);
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
