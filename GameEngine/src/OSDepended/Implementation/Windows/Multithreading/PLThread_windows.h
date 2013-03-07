/*
 * PLThread_windows.h
 *
 *  Created on: Jan 22, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLTHREAD_WINDOWS_H_
#define PLTHREAD_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#include "../../../Interface/Multithreading/IPLThread.h"

#include "../EventHandling/PLRunLoop_windows.h"

///////////////////////////////////////////////////////////////////////////////
class PLThread_windows : public IPLThread
{
private:

	//
	typedef struct
	{
		void *argument;
		PLThreadEnterPointFunction *function;
	}
	EnterPoint;

	//
	HANDLE _threadHandle;
	EnterPoint *_enterPoint;

	//
	PLRunLoop_windows *_runLoop;

	//
	PLThread_windows(HANDLE inThreadHandle,
			PLThreadEnterPointFunction *inFunction);

	//
	friend DWORD threadEnterFunction(LPVOID inArgument);

public:


	//
	//
	PLThread_windows(PLThreadEnterPointFunction *inFunction);

	virtual ~PLThread_windows();

	//
	virtual void runWithArgument(void *inArgument);

	//
	virtual IPLRunLoop *runLoop();

	// TODO: Put static methods to interface if it's possible
	static void createMainThreadObject(HANDLE inHandle);
	static PLThread_windows *currentThread();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLTHREAD_WINDOWS_H_ */
