/*
 * PLWindow.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLWINDOW_INTERFACE_H_
#define PLWINDOW_INTERFACE_H_

///////////////////////////////////////////////////////////////////////////////
#include "EventHandling/PLRunLoop_interface.h"

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
class PLWindow_interface
{
public:
	virtual void show() = 0;
	virtual void getGLContext() = 0;
	virtual void setFocus() = 0;

	virtual PLRunLoop_interface *getRunLoop() = 0;

//	virtual void getGLContext();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLWINDOW_INTERFACE_H_ */
