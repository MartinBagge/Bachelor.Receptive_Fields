/*
 * Parallelize.h
 *
 *  Created on: Apr 24, 2016
 *      Author: martin
 */

#ifndef PARALLELIZE_H_
#define PARALLELIZE_H_
#ifdef __CUDACC__
#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
#define CUDA_CALLABLE_MEMBER
#endif

#include <cuda_runtime_api.h>
#include <cuda.h>
#include <math.h>
#include <device_launch_parameters.h>
#include <vector>

class Parallelize {
	public:
		Parallelize();
		~Parallelize();
		std::vector<double> createKernels(std::vector<double> centers, double step, double width, int size);
	private:
		void d_createKernels(double *centers, double step, double width, double *kernelsArr);
		__global__ void d_createKernel(double *center, double *step, double *width, double *kernel, int size);
};
#endif /* PARALLELIZE_H_ */

