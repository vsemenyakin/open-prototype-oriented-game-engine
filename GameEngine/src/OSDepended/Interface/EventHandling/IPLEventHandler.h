/*
 * IPLEventHandler.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLEVENTHANDLER_H_
#define IPLEVENTHANDLER_H_

///////////////////////////////////////////////////////////////////////////////
#include <list>

///////////////////////////////////////////////////////////////////////////////
typedef unsigned int PLEventMessage;
typedef std::list<PLEventMessage> PLHandlerRegistringInformation;

typedef void (*PLEventCallback)(void *inMessage);

///////////////////////////////////////////////////////////////////////////////
class IPLEventHandler
{
public:
	virtual ~IPLEventHandler() { };

	virtual PLHandlerRegistringInformation *getRegistringInformation() = 0;
	virtual void addCallback(PLEventCallback inCallback) = 0;
};

#endif /* IPLEVENTHANDLER_H_ */
