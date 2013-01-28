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

#include "../../../Interface/Multithreading/PLThread_interface.h"

///////////////////////////////////////////////////////////////////////////////
class PLThread_windows : public PLThread_interface
{
private:
	typedef struct
	{
		void *argument;
		PLThreadEnterPointFunction *function;
	} EnterPoint;


	HANDLE _threadHandle;
	PLThreadEnterPointFunction *_enterPointFunction;

	//
	friend DWORD threadFunctionMapping(LPVOID inArgument);

public:
	//
	//
	PLThread_windows(PLThreadEnterPointFunction *inFunction);
	virtual ~PLThread_windows();

	//
	virtual void runWithArgument(void *inArgument);
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLTHREAD_WINDOWS_H_ */
