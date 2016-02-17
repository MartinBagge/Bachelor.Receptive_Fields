/*
 * ReceptiveFields.h
 *
 *  Created on: Feb 17, 2016
 *      Author: martin
 */

#ifndef RECEPTIVEFIELDS_H_
#define RECEPTIVEFIELDS_H_

class ReceptiveFields {

	public:
		ReceptiveFields(const int lowerLimit, const int upperLimit, const int numberOfKernels);
		virtual ~ReceptiveFields();
	private:
		const int lowerLimit;
		const int upperLimit;
		const int numberOfKernels;

		virtual void createGaussianKernels();
		virtual void applyDeltaRule(int iterations);
};

#endif /* RECEPTIVEFIELDS_H_ */
