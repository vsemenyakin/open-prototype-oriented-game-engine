/*
 * PLRunLoop.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLRunLoop_windows.h"

#include <iostream.h>

///////////////////////////////////////////////////////////////////////////////
PLRunLoop_windows::PLRunLoop_windows()
{
}

PLRunLoop_windows::~PLRunLoop_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLRunLoop_windows::assignHandler(IPLEventHandler_windows *inHandler)
{
	PLHandlerRegistringInformation *theRegistringInformation =
			inHandler->getRegistringInformation();

	PLHandlerRegistringInformation::iterator theIterator =
			theRegistringInformation->begin();
	for (; theIterator != theRegistringInformation->end(); ++theIterator)
	{
		_messageHandlersAssigning[*theIterator] = inHandler;
	}
}

///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK PLRunLoop_windows::windowProcedure(HWND inWindowHandle,
		UINT inMessage, WPARAM inWindowParameter, LPARAM inD)
{
	IPLEventHandler_windows *theHandler = _messageHandlersAssigning[inMessage];
	if (NULL != theHandler)
	{
		_messageHandlersAssigning[inMessage]->handleEvent(inWindowHandle,
				inMessage, inWindowParameter, inD);
	}

	return DefWindowProc(inWindowHandle, inMessage, inWindowParameter, inD);
}
