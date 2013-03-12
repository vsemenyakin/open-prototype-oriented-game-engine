/*
 * PLKeyboardEventHandler.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLKEYBOARDEVENTHANDLER_WINDOWS_H_
#define PLKEYBOARDEVENTHANDLER_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include "IPLEventHandler_windows.h"

///////////////////////////////////////////////////////////////////////////////
class PLKeyboardEventHandler_windows : public IPLEventHandler_windows
{
private:
	PLEventCallback _callback;

public:
	PLKeyboardEventHandler_windows();
	virtual ~PLKeyboardEventHandler_windows();

	virtual PLHandlerRegistringInformation *getRegistringInformation();
	virtual void handleEvent(MSG inMessage);

	virtual void addCallback(PLEventCallback inCallback);
};

#endif /* PLKEYBOARDEVENTHANDLER_WINDOWS_H_ */
