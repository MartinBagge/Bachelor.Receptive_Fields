/*
 * ReceptiveFields.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#include "ReceptiveFields.h"


ReceptiveFields::ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels) : LOWER_LIMIT(lowerLimit), UPPER_LIMIT(upperLimit), NUMBER_OF_KERNELS(numberOfKernels){

}

void ReceptiveFields::createGaussianKernels(){

}

void ReceptiveFields::applyDeltaRule(int iterations){
	for(int i; i < iterations; i++){

	}
}

ReceptiveFields::~ReceptiveFields() {
	// TODO Auto-generated destructor stub
}

