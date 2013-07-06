/*
 * IPLRunLoop_interface.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLRUNLOOP_H_
#define IPLRUNLOOP_H_

///////////////////////////////////////////////////////////////////////////////
#include <application/interface/event_handling/IPLRunLoopService.h>

#include <core/PLString.h>

///////////////////////////////////////////////////////////////////////////////
class IPLRunLoop
{
public:
	virtual ~IPLRunLoop() { }

	virtual void run() = 0;

	virtual void addService(IPLRunLoopService *inService) = 0;
	virtual IPLRunLoopService *serviceForKey(PLString &inKey) = 0;
};

#endif /* IPLRUNLOOP_H_ */
