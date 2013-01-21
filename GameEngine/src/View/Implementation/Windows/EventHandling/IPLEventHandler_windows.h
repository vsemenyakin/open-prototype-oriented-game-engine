/*
 * PLEventHandler.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLEVENTHANDLER_H_
#define IPLEVENTHANDLER_H_

///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <list>

#include "../../../Interface/PLGraphic_interface.h"

///////////////////////////////////////////////////////////////////////////////
typedef UINT PLEventMessage;
typedef std::list<PLEventMessage> PLHandlerRegistringInformation;

typedef void (*PLEventCallback)(void *inMessage);

///////////////////////////////////////////////////////////////////////////////
class IPLEventHandler_windows : public IPLEventHandler_interface
{
public:
	virtual PLHandlerRegistringInformation *getRegistringInformation() = 0;
	virtual void addCallback(PLEventCallback inCallback) = 0;

	virtual void handleEvent(HWND inWindowHandle, UINT inMessage,
			WPARAM inWindowParameter, LPARAM inD) = 0;
};

#endif /* PLEVENTHANDLER_H_ */
