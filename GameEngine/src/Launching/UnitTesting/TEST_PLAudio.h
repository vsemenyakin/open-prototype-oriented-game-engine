/*
 * TEST_PLAudio.h
 *
 *  Created on: 28.01.2013
 *      Author: ����
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef TEST_PLAUDIO_H_
#define TEST_PLAUDIO_H_

///////////////////////////////////////////////////////////////////////////////
#include "IPLUnitTest.h"

///////////////////////////////////////////////////////////////////////////////
class TEST_PLAudio : public IPLUnitTest
{
public:
	TEST_PLAudio();
	virtual ~TEST_PLAudio();

	virtual void performTest();
};

#endif /* TEST_PLAUDIO_H_ */
