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

#include <application/implementation/event_handling/PLRunLoop/PLRunLoop_windows.h>

///////////////////////////////////////////////////////////////////////////////
class PLThread_windows : public IPLThread
{
private:

	// **************************************************************
	// *					Private _ Types							*
	// **************************************************************
	typedef struct
	{
		void *argument;
		PLThreadEnterPointFunction *function;
	}
	EnterPoint;


	// **************************************************************
	// *					Private _ Fields						*
	// **************************************************************

	// Handle to windows thread
	HANDLE _threadHandle;

	// PL thread object enter point
	EnterPoint *_enterPoint;

	// Runloop of thread
	PLRunLoop_windows *_runLoop;


	// **************************************************************
	// *					Private _ Methods						*
	// **************************************************************

	// =====================
	// *** Memory management

	// Windows handle based thread constructor.
	// Needs for assigning the windows thread
	// handle and PL thread object handle.
	PLThread_windows(HANDLE inThreadHandle,
			PLThreadEnterPointFunction *inFunction);

	// **************************************************************
	// *					Private _ Friends						*
	// **************************************************************

	// Windows thread enter point.
	// This function calls when windows thread starts. Then it cast input
	// argument to PL thread object enter point (PLThread_windows::EnterPoint)
	// and launch enter point function with enter point argument.
	friend DWORD threadEnterFunction(LPVOID inArgument);

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// =====================
	// *** Memory management
	PLThread_windows(PLThreadEnterPointFunction *inFunction);
	virtual ~PLThread_windows();


	// ===============================
	// *** [IMPLEMENTATION: IPLThread]
	virtual void runWithArgument(void *inArgument);
	virtual IPLRunLoop *runLoop();


	// ==================
	// *** Static methods
	static void createMainThreadObject(HANDLE inHandle);
	static PLThread_windows *currentThread();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLTHREAD_WINDOWS_H_ */
