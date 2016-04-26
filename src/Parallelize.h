/*
 * Parallelize.h
 *
 *  Created on: Apr 24, 2016
 *      Author: martin
 */

#ifndef PARALLELIZE_H_
#define PARALLELIZE_H_

#include <cuda_runtime_api.h>
#include <cuda.h>
#include <math.h>
#include <device_launch_parameters.h>
#include <vector>
#include <iostream>
#include <stdio.h>

class Parallelize {
	public:
		Parallelize();
		~Parallelize();
		//GENERAL
		//Call function to create "step" in kernel
		std::vector<double> createKernels(std::vector<double> centers, double step, double width, int size);
		//LEARNING
		//function for simple supervised learning
		std::vector<double> applyDeltaRule(double learningRate, std::vector<double> centers, std::vector<double> target, std::vector<double> weights, std::vector<double> kernels, int learningIterations);
	private:
		//prepare functions
		void d_createKernels(double *centers, double step, double width, double *kernelsArr, int centerSize, int kernelSize);
		//learning
		void calcOutput(double *weights, double *kernels, double *output, int centerSize, int targetSize, int kernelSize);
		void updateWeights(double learningRateValue, double *centers, double *target, double *output, double *weights, int centerSize, int targetSize);
};
#endif /* PARALLELIZE_H_ */

