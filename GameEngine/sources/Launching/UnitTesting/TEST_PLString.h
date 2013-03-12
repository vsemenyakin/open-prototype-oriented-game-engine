/*
 * TEST_PLString.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef TEST_PLSTRING_H_
#define TEST_PLSTRING_H_

///////////////////////////////////////////////////////////////////////////////
#include "PLUnitTestCore.h"
#include <core/PLString.h>

///////////////////////////////////////////////////////////////////////////////
class TEST_PLString : public IPLUnitTest
{
private:
	PLString _string;

public:
	TEST_PLString();
	virtual ~TEST_PLString();

	virtual void performTest();
};

#endif /* TEST_PLSTRING_H_ */
