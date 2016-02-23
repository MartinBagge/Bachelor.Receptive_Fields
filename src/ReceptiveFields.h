/*
 * ReceptiveFields.h
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#ifndef RECEPTIVEFIELDS_H_
#define RECEPTIVEFIELDS_H_

#include <cmath>

class ReceptiveFields {

	public:
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningRate, const int targetSize);
		virtual ~ReceptiveFields();
		virtual std::string toString();
	private:
		const int lowerLimit;
		const int upperLimit;
		const int numberOfKernels;
		const double kernelWidth;

		double gaussianKernels[][];
		double kernelCenters[];
		double weights[][];
		double transKernels[][];
		double transWeights[][];
		double transOutput[][];
		double output[][];
		double targetPattern[];

		virtual void createGaussianKernels();
		virtual void linSpace(int start, int stop, int space, double *returnArray);
		virtual void zeros(double *returnArray);
		virtual void transposeMatrix(double *initialArray, double *returnArray);

		//Learning properties
		double alfa[];
		const double learningRate;
		const int learningRateIterations;

		virtual void applyDeltaRule();

		//Learning target
		const int targetSize;
		double target[];

		virtual void genTargetPattern(double *returnArray);
};

#endif /* RECEPTIVEFIELDS_H_ */
