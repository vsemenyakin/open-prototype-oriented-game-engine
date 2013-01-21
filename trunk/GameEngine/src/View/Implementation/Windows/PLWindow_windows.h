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

#include "../../../Base/PLCore.h"
#include "EventHandling/PLRunLoop_windows.h"

///////////////////////////////////////////////////////////////////////////////
class PLWindow_windows
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

public:
	PLWindow_windows(char *inName, PLRectange inFrame);
	virtual ~PLWindow_windows();

	void show();
	void getGLContext();
	void setFocus();

	PLRunLoop_windows *getRunLoop();
};

///////////////////////////////////////////////////////////////////////////////
#define PLWindow PLWindow_windows

#endif /* PLWINDOW_WINDOWS_H_ */
