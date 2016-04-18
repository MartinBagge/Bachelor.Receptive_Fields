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
#include <fstream>
//#include "boost/multi_array.hpp"

class ReceptiveFields {

	public:
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize);

		~ReceptiveFields();

		virtual void toString();
		virtual void genTargetPattern(double (*func)(int));
		virtual void generateTarget(double input);
		virtual void createGaussianKernels();
		virtual void generateAlfaPattern();
	private:
		int targetcount;
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



		virtual std::vector<double> linSpaceDouble(int start, int stop, int space);
		virtual std::vector<int> linSpaceInt(int start, int stop, int space);
		virtual std::vector<double> zeros(int size);

		//Learning properties


		const double learningRate;
		const int learningIterations;

		virtual void applyDeltaRule();

		//Learning target

		const int targetSize;

};
#endif /* RECEPTIVEFIELDS_H_ */
