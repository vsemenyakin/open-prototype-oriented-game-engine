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
	void assignHandler(IPLEventHandler *inHandler);
};

#endif /* IPLRUNLOOP_H_ */