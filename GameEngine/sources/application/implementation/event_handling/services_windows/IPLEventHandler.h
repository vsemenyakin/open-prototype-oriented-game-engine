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

///////////////////////////////////////////////////////////////////////////////
//! Structure that saves all windows messages that processed by current handler
typedef std::list<UINT> PLHandlerRegistringInformation;

///////////////////////////////////////////////////////////////////////////////
class IPLEventHandler
{
public:
	virtual ~IPLEventHandler() { }

	virtual PLHandlerRegistringInformation *getRegistringInformation() = 0;
	virtual void handleEvent(MSG &inMessage) = 0;
};

#endif /* IPLEVENTHANDLER_H_ */
