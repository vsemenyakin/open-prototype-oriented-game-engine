/*
 * PLWindowEventsService.h
 *
 *  Created on: 21.03.2013
 *      Author: semenyakinVS
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLWINDOWEVENTSSERVICE_H_
#define PLWINDOWEVENTSSERVICE_H_

///////////////////////////////////////////////////////////////////////////////
#include <application/interface/event_handling/IPLRunLoopService.h>

#include <application/implementation/event_handling/services_windows/IPLEventHandler.h>

#include <map>

///////////////////////////////////////////////////////////////////////////////
static PLString kPLRunLoopServiceWindowEvent("kPLRunLoopServiceWindowEvent");

///////////////////////////////////////////////////////////////////////////////
class PLWindowEventsService : public IPLRunLoopService
{
private:
	std::map<UINT, IPLEventHandler *> _messageHandlersAssigning;

public:
	PLWindowEventsService();
	virtual ~PLWindowEventsService();

	virtual void activateService();

	virtual void assignHandler(IPLEventHandler *inHandler);

	virtual PLString &key();

	//	LRESULT CALLBACK windowProcedure(HWND inWindowHandle, UINT inMessage,
	//			WPARAM inWindowParameter, LPARAM inD);
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLWINDOWEVENTSSERVICE_H_ */
