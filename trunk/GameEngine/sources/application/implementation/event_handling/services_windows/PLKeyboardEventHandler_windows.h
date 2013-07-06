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
#include <application/implementation/event_handling/services_windows/IPLEventHandler.h>

#include <core/PLEventCenter.h>

///////////////////////////////////////////////////////////////////////////////
DECLARE_EVENT_KEY(kPLKeyDownEvent)
DECLARE_EVENT_KEY(kPLKeyUpEvent)

///////////////////////////////////////////////////////////////////////////////
class PLKeyboardEventHandler_windows : public IPLEventHandler
{
public:
	PLKeyboardEventHandler_windows();
	virtual ~PLKeyboardEventHandler_windows();

	virtual PLHandlerRegistringInformation *getRegistringInformation();

	// Get and process windows message
	virtual void handleEvent(MSG &inMessage);
};

#endif /* PLKEYBOARDEVENTHANDLER_WINDOWS_H_ */
