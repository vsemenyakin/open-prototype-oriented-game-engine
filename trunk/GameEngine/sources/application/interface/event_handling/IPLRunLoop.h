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
#include "IPLEventHandler.h"

///////////////////////////////////////////////////////////////////////////////
class IPLRunLoop
{
public:
	virtual ~IPLRunLoop() { }

	virtual void assignHandler(IPLEventHandler *inHandler) = 0;
	virtual void run() = 0;
};

#endif /* IPLRUNLOOP_H_ */
