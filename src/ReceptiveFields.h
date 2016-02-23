/*
 * ReceptiveFields.h
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#ifndef RECEPTIVEFIELDS_H_
#define RECEPTIVEFIELDS_H_

#include <cmath>
#include <string>
#include <iostream>
using namespace std;

class ReceptiveFields {

	public:
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize);
		virtual ~ReceptiveFields();
		virtual void toString();
	private:
		const int lowerLimit;
		const int upperLimit;
		const int numberOfKernels;
		const double kernelWidth;

		double** gaussianKernels;
		double* kernelCenters;
		double** weights;
		double** transKernels;
		double** transWeights;
		double** transOutput;
		double** output;
		double* targetPattern;

		virtual void createGaussianKernels();
		virtual void linSpace(int start, int stop, int space, double *returnArray);
		virtual void zeros(double **returnArray);
		virtual void transposeMatrix(double **initialArray, double **returnArray);

		//Learning properties
		double* alfa;
		const double learningRate;
		const int learningIterations;

		virtual void applyDeltaRule();

		//Learning target
		const int targetSize;
		double* target;

		virtual void genTargetPattern(double *returnArray);
};

#endif /* RECEPTIVEFIELDS_H_ */
