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

__global__
void Parallelize::d_createKernel(double *center, double *step, double *width, double *kernel, int size){
	int i = threadIdx.x;
	if(i < size)
		*kernel = exp((-(((*center)-(*step))*((*center)-(*step)))/2)*(*width));
}

void Parallelize::d_createKernels(double *centers, double step, double width, double *kernelsArr){
	  int N = sizeof(centers);
	  double stepArr[1], widthArr[1], *d_kernelCenter, *d_step, *d_kernelWidth, *d_kernel;


	  cudaMalloc((void**)&d_kernelCenter, N*sizeof(double));
	  cudaMalloc((void**)&d_step, N*sizeof(double));
	  cudaMalloc((void**)&d_kernelWidth, N*sizeof(double));
	  cudaMalloc((void**)&d_kernel, N*sizeof(double));


	  for(int i = 0; i < N; i++){
		  stepArr[i] = step;
		  widthArr[i] = width;
		  kernelsArr[i] = 0;
	  }

	  cudaMemcpy(d_kernelCenter, centers, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_step, stepArr, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernelWidth, widthArr, N*sizeof(double), cudaMemcpyHostToDevice);
	  cudaMemcpy(d_kernel, kernelsArr, N*sizeof(double), cudaMemcpyHostToDevice);

	  //function call
	  d_createKernel<<<1,N>>>(d_kernelCenter, d_step, d_kernelWidth, d_kernel, N);

	  cudaDeviceSynchronize();

	  cudaMemcpy(centers, d_kernelCenter, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(stepArr, d_step, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(widthArr, d_kernelWidth, N*sizeof(double), cudaMemcpyDeviceToHost);
	  cudaMemcpy(kernelsArr, d_kernel, N*sizeof(double), cudaMemcpyDeviceToHost);


	  cudaFree(d_kernelCenter);
	  cudaFree(d_step);
	  cudaFree(d_kernelWidth);
	  cudaFree(d_kernel);


}

std::vector<double> Parallelize::createKernels(std::vector<double> centers, double step, double width, int size){
	double* centersArr = &centers[0];
	double* kernelsArr = new double[size];
	d_createKernels(centersArr, step, width, kernelsArr);
	std::vector<double> returnVector;
	for(int i = 0; i < sizeof(kernelsArr); i++){
		returnVector.push_back(kernelsArr[i]);
	}
	return returnVector;
}
