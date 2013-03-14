/*
 * PLEventHandler.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLEVENTHANDLER_WINDOWS_H_
#define IPLEVENTHANDLER_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <list>

#include <application/interface/event_handling/IPLEventHandler.h>

///////////////////////////////////////////////////////////////////////////////
typedef UINT PLEventMessage;
typedef std::list<PLEventMessage> PLHandlerRegistringInformation;

typedef void (*PLEventCallback)(void *inMessage);

///////////////////////////////////////////////////////////////////////////////
class IPLEventHandler_windows : public IPLEventHandler
{
public:
	virtual PLHandlerRegistringInformation *getRegistringInformation() = 0;
	virtual void addCallback(PLEventCallback inCallback) = 0;

	virtual void handleEvent(MSG inMessage) = 0;
};

#endif /* IPLEVENTHANDLER_WINDOWS_H_ */
