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
#include "Parallelize.h"

class ReceptiveFields {

	public:
		//FUNCTIONS
		
		//if use_gpu is set to true a nvidia gpu must be present in the system setup as this is required
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels, const double kernelWidth, const double learningRate, const int learningIterations, const int targetSize,  bool use_gpu);

		~ReceptiveFields();
		//Used to create a value in each kernel
		virtual void createStep(double step);
		//Call when all steps are added to apply learning
		virtual void applyDeltaRule();
		//TODO: debugging
		virtual void toString();
		//Method is used to give one point in the learning trajectory
		virtual void generateTarget(double input);
		
		
		
		//PROPERTIES
		//GPU properties
		Parallelize* para;
		const bool use_gpu;
		
		//Generel properties
		int kernelCreationCounter;
		const int lowerLimit;
		const int upperLimit;
		const int numberOfKernels;
		const double kernelWidth;
		std::vector<double> gaussianKernels2d;
		std::vector<double> kernelCenters1d;
		std::vector<double> output1d;
		virtual std::vector<double> linSpace(double start, double stop, double space);
		virtual std::vector<double> zeros(int size);
		
		//Properties for learning
		std::vector<double> OutputsizeToCentersize;
		std::vector<double> alfa1d;
		std::vector<double> weights1d;
		std::vector<double> targetPattern1d;
		int targetcount;
		const double learningRate;
		const int learningIterations;
		const int targetSize;

};
#endif /* RECEPTIVEFIELDS_H_ */
