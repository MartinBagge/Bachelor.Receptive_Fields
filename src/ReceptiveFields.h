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
#include <vector>
//#include "boost/multi_array.hpp"

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
/*
		typedef boost::multi_array<double, 2> twoDimArray;
		typedef twoDimArray::index index;

		typedef boost::multi_array<double, 1> oneDimArray;

		twoDimArray gaussianKernels;
		oneDimArray kernelCenters;
		oneDimArray alfa;
		twoDimArray weights;
		oneDimArray targetPattern;
		twoDimArray transKernels;
		twoDimArray transWeights;
		twoDimArray transOutput;
		twoDimArray output;
*/

		std::vector<double> gaussianKernels2d;
		std::vector<double> kernelCenters1d;
		std::vector<double> alfa1d;
		std::vector<double> weights1d;
		std::vector<double> targetPattern1d;
		std::vector<double> transKernels2d;
		//std::vector<double> transWeights1d;
		//std::vector<double> transOutput1d;
		std::vector<double> output1d;


		virtual void createGaussianKernels();
		virtual void linSpace(int start, int stop, int space, std::vector<double> returnArray);
		virtual void zeros(std::vector<double> returnVector);
		virtual void transposeMatrix(std::vector<double> initialArray, std::vector<double> returnArray, int numberOfDims);

		//Learning properties


		const double learningRate;
		const int learningIterations;

		virtual void applyDeltaRule();

		//Learning target

		const int targetSize;

		virtual void genTargetPattern(std::vector<double> returnArray);
};
#endif /* RECEPTIVEFIELDS_H_ */
