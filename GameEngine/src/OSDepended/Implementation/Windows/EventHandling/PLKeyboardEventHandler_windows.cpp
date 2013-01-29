/*
 * PLKeyboardEventHandler.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLKeyboardEventHandler_windows.h"
#include <windows.h>

#include <iostream.h>

///////////////////////////////////////////////////////////////////////////////
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
void PLKeyboardEventHandler_windows::handleEvent(MSG inMessage)
{
	std::cout << "<Key pressed event>" << std::endl;
	std::cout << "Time: " << inMessage.time << std::endl;
	std::cout << "Information: " << inMessage.wParam << std::endl;

	(*_callback)(new unsigned int(0));
}

///////////////////////////////////////////////////////////////////////////////
void PLKeyboardEventHandler_windows::addCallback(PLEventCallback inCallback)
{
	_callback = inCallback;
}