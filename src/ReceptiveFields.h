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
#include <vector>
//TODO: delete when testing is done
#include <iostream>
#include <fstream>
#include "Parallelize.cuh"

class ReceptiveFields {

	public:
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize);

		~ReceptiveFields();
		//TODO: delete toString method when testing is done
		virtual void createStep(double step);
		virtual void applyDeltaRule();
		
		//Method is used to give one point in the learning trajectory
		virtual void generateTarget(double input);
	private:
		Parallelize para;
		int kernelCreationCounter;
		const int lowerLimit;
		const int upperLimit;
		const int numberOfKernels;
		const double kernelWidth;
	
		std::vector<double> gaussianKernels2d;
		std::vector<double> kernelCenters1d;
		std::vector<double> alfa1d;
		std::vector<double> weights1d;
		std::vector<double> output1d;


		//Util methods
		virtual std::vector<double> linSpace(double start, double stop, double space);
		virtual std::vector<double> zeros(int size);

		//Learning properties

		int targetcount;
		const double learningRate;
		const int learningIterations;
		const int targetSize;
		
		std::vector<double> targetPattern1d;


};
#endif /* RECEPTIVEFIELDS_H_ */
