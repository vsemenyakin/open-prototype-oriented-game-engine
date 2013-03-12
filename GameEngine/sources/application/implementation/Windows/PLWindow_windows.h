/*
 * PLWindow.h
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

#ifndef PLWINDOW_WINDOWS_H_
#define PLWINDOW_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#include "EventHandling/PLRunLoop_windows.h"

#include "../../Interface/IPLWindow.h"

///////////////////////////////////////////////////////////////////////////////
class PLWindow_windows : public IPLWindow
{
private:
	// Low level properties
	WNDCLASSEX *_windowClass;
	HWND _windowHandle;

	// High level properties
	char *_name;
	PLRectange _frame;

	/////////////////
	PLRunLoop_windows *_runLoop;


	WNDCLASSEX *createWindowClass(const char *inName);


public:
	PLWindow_windows(char *inName, PLRectange inFrame);
	virtual ~PLWindow_windows();

	virtual void show();
	virtual void getGLContext();
	virtual void setFocus();

	virtual PLRunLoop_windows *getRunLoop();
};

#endif /* PLWINDOW_WINDOWS_H_ */
