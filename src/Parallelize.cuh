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

#include <vector>
#include <iostream>

class Parallelize {
	public:
	CUDA_CALLABLE_MEMBER Parallelize();
	CUDA_CALLABLE_MEMBER ~Parallelize();

	CUDA_CALLABLE_MEMBER std::vector<double> createKernels(std::vector<double> centers, double step, double width, int size);
	private:
};
#endif /* PARALLELIZE_H_ */

