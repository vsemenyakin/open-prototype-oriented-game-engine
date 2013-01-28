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
#include "IPLEventHandler_windows.h"

#include <windows.h>
#include <map>

#include "../../../Interface/PLGraphic_interface.h"

///////////////////////////////////////////////////////////////////////////////
class PLRunLoop_windows : public PLRunLoop_interface
{
private:
	std::map<PLEventMessage, IPLEventHandler_windows *>
			_messageHandlersAssigning;

	HDC ___handle;

public:
	PLRunLoop_windows();
	virtual ~PLRunLoop_windows();

	void assignHandler(IPLEventHandler_windows *inHandler);
	void run();

	void setHandle(HDC inHandle);

	LRESULT CALLBACK windowProcedure(HWND inWindowHandle, UINT inMessage,
			WPARAM inWindowParameter, LPARAM inD);
};

#endif /* PLRUNLOOP_WINDOWS_H_ */
