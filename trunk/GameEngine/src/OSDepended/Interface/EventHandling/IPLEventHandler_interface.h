/*
 * IPLEventHandler_interface.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLEVENTHANDLER_INTERFACE_H_
#define IPLEVENTHANDLER_INTERFACE_H_

///////////////////////////////////////////////////////////////////////////////
typedef unsigned int PLEventMessage;
typedef std::list<PLEventMessage> PLHandlerRegistringInformation;

typedef void (*PLEventCallback)(void *inMessage);

///////////////////////////////////////////////////////////////////////////////
class IPLEventHandler_interface
{
public:
	virtual PLHandlerRegistringInformation *getRegistringInformation() = 0;
	virtual void addCallback(PLEventCallback inCallback) = 0;
};

#endif /* IPLEVENTHANDLER_INTERFACE_H_ */
