/*
 * PLKeyboardEventHandler.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLKeyboardEventHandler_windows.h"
#include <windows.h>

PLKeyboardEventHandler_windows::PLKeyboardEventHandler_windows()
{
}

PLKeyboardEventHandler_windows::~PLKeyboardEventHandler_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
static PLHandlerRegistringInformation sKeyboardRegistringInformation;

PLHandlerRegistringInformation
		*PLKeyboardEventHandler_windows::getRegistringInformation()
{
	if (sKeyboardRegistringInformation.size() == 0)
	{
		sKeyboardRegistringInformation.push_back(WM_KEYDOWN);
		sKeyboardRegistringInformation.push_back(WM_KEYUP);
	}

	return &sKeyboardRegistringInformation;
}

///////////////////////////////////////////////////////////////////////////////
void PLKeyboardEventHandler_windows::handleEvent(HWND inWindowHandle,
		UINT inMessage, WPARAM inWindowParameter, LPARAM inD)
{
	(*_callback)(new unsigned int(inWindowParameter));
}

///////////////////////////////////////////////////////////////////////////////
void PLKeyboardEventHandler_windows::addCallback(PLEventCallback inCallback)
{
	_callback = inCallback;
}
