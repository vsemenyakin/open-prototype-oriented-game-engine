/*
 * PLUnitTest.h
 *
 *  Created on: Aug 30, 2012
 *      Author: Admin
 */

#ifndef PLUNITTEST_H_
#define PLUNITTEST_H_

class IPLUnitTest
{
public:
	virtual ~IPLUnitTest() { };
	virtual void performTest() = 0;
};

#endif /* PLUNITTEST_H_ */
