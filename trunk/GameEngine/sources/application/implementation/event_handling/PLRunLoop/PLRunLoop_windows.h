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
#include <application/implementation/event_handling/PLEventHandler/IPLEventHandler_windows.h>

#include <windows.h>
#include <map>

#include <application/interface/event_handling/IPLRunLoop.h>

///////////////////////////////////////////////////////////////////////////////
class PLRunLoop_windows : public IPLRunLoop
{
private:
	std::map<PLEventMessage, IPLEventHandler *>
			_messageHandlersAssigning;

	HDC ___handle;

public:
	PLRunLoop_windows();
	virtual ~PLRunLoop_windows();

	virtual void assignHandler(IPLEventHandler *inHandler);
	virtual void run();

//	void setHandle(HDC inHandle);

	LRESULT CALLBACK windowProcedure(HWND inWindowHandle, UINT inMessage,
			WPARAM inWindowParameter, LPARAM inD);
};

#endif /* PLRUNLOOP_WINDOWS_H_ */
