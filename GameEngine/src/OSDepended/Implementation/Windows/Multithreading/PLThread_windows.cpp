/*
 * PLThread_windows.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLThread_windows.h"

#include <map>

#include <iostream.h>

///////////////////////////////////////////////////////////////////////////////
DWORD threadFunctionMapping(LPVOID inArgument)
{
	PLThread_windows::EnterPoint *theEnterPoint =
			(PLThread_windows::EnterPoint *)inArgument;
	theEnterPoint->function(theEnterPoint->argument);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
PLThread_windows::PLThread_windows(PLThreadEnterPointFunction *inFunction)
{
	_enterPointFunction = inFunction;
}

PLThread_windows::~PLThread_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLThread_windows::runWithArgument(void *inArgument)
{
	EnterPoint *theEnterPoint = new EnterPoint();

	theEnterPoint->function = _enterPointFunction;
	theEnterPoint->argument = inArgument;

	// Create thread
	_threadHandle = CreateThread(NULL, 0,
			(LPTHREAD_START_ROUTINE)threadFunctionMapping,
			(PVOID *)theEnterPoint, 0, NULL);
}
