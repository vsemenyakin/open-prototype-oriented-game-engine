/*
 * PLRunLoop.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLRunLoop_windows.h"

#include <algorithm> // std::for_each

///////////////////////////////////////////////////////////////////////////////
PLRunLoop_windows::PLRunLoop_windows()
	: _services()
{
}

PLRunLoop_windows::~PLRunLoop_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLRunLoop_windows::run()
{
	bool theExecutingFlag = true;

	while (theExecutingFlag)
	{
		for (AServicesMap::iterator theIterator = _services.begin();
				theIterator != _services.end(); ++theIterator)
		{
			theIterator->second->activateService();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
void PLRunLoop_windows::addService(IPLRunLoopService *inService)
{
	_services[inService->key()] = inService;
}

IPLRunLoopService *PLRunLoop_windows::serviceForKey(PLString &inKey)
{
	return _services[inKey];
}
