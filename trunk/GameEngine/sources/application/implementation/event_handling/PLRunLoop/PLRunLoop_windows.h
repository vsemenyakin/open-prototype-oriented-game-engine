/*
 * PLRunLoop.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLRUNLOOP_WINDOWS_H_
#define PLRUNLOOP_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include <application/interface/event_handling/IPLRunLoop.h>

#include <core/PLString.h>

#include <map>

///////////////////////////////////////////////////////////////////////////////
class PLRunLoop_windows : public IPLRunLoop
{
private:

	typedef std::map<PLString, IPLRunLoopService *> AServicesMap;
	AServicesMap _services;

public:

	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// =====================
	// *** Memory management
	PLRunLoop_windows();
	virtual ~PLRunLoop_windows();

	// ===============================
	// *** [IMPLEMENTATION: IPLRunLoop]
	virtual void run();

	virtual void addService(IPLRunLoopService *inService);
	virtual IPLRunLoopService *serviceForKey(PLString &inKey);
};

#endif /* PLRUNLOOP_WINDOWS_H_ */
