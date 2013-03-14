/*
 * PLThread_interface.h
 *
 *  Created on: Jan 24, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLTHREAD_H_
#define IPLTHREAD_H_

///////////////////////////////////////////////////////////////////////////////
#include <application/interface/event_handling/IPLRunLoop.h>

///////////////////////////////////////////////////////////////////////////////
typedef unsigned int PLThreadPerforingResult;
typedef PLThreadPerforingResult (PLThreadEnterPointFunction)(void *);

///////////////////////////////////////////////////////////////////////////////
class IPLThread
{
public:
	virtual ~IPLThread(){}

	virtual void runWithArgument(void *inArgument) = 0;
	virtual IPLRunLoop *runLoop() = 0;
};

#endif /* IPLTHREAD_H_ */
