/*
 * PLThread_windows.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLThread_windows.h"

#include <map>

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// | ********************************************* |
// | *** OS thread to framework thread mapping *** |
// | ********************************************* |
///////////////////////////////////////////////////////////////////////////////
// *** Mapping data structure
static std::map<HANDLE, PLThread_windows *> sThreadMapping;

///////////////////////////////////////////////////////////////////////////////
// *** Thread registry data structure
DWORD threadEnterFunction(LPVOID inArgument)
{
	PLThread_windows::EnterPoint *theEnterPoint =
			(PLThread_windows::EnterPoint *)inArgument;

	return (DWORD)theEnterPoint->function(theEnterPoint->argument);
}

///////////////////////////////////////////////////////////////////////////////
// | ******************** |
// | *** Thread class *** |
// | ******************** |
///////////////////////////////////////////////////////////////////////////////
PLThread_windows::PLThread_windows(PLThreadEnterPointFunction *inFunction)
	: _threadHandle(0), _enterPoint(new EnterPoint()), _runLoop(NULL)
{
	_enterPoint->function = inFunction;
}

// Private constructor
PLThread_windows::PLThread_windows(HANDLE inThreadHandle,
		PLThreadEnterPointFunction *inFunction)
	: _threadHandle(inThreadHandle), _enterPoint(new EnterPoint()),
	  _runLoop(NULL)
{
	_enterPoint->function = inFunction;
}

PLThread_windows::~PLThread_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLThread_windows::runWithArgument(void *inArgument)
{
	if (0 == _threadHandle)
	{
		_enterPoint->argument = inArgument;

		// Create thread
		_threadHandle = CreateThread(NULL, 0,
				(LPTHREAD_START_ROUTINE)threadEnterFunction,
				(PVOID *)_enterPoint, 0, NULL);

		sThreadMapping[_threadHandle] = this;
	}
}

///////////////////////////////////////////////////////////////////////////////
void PLThread_windows::createMainThreadObject(HANDLE inHandle)
{
	sThreadMapping[inHandle] =  new PLThread_windows(inHandle, NULL);
}

///////////////////////////////////////////////////////////////////////////////
IPLRunLoop *PLThread_windows::runLoop()
{
	if (NULL == _runLoop)
	{
		_runLoop = new PLRunLoop_windows();
	}

	return _runLoop;
}

///////////////////////////////////////////////////////////////////////////////
PLThread_windows *PLThread_windows::currentThread()
{
	return sThreadMapping[GetCurrentThread()];
}
