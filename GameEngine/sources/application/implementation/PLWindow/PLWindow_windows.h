/*
 * PLWindow.h
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

#ifndef PLWINDOW_WINDOWS_H_
#define PLWINDOW_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
// Windows OS
#include <windows.h>

// Interface
#include <application/interface/IPLWindow.h>
#include <core/IPLCompositeEventSource.h>

// Runloop object
#include <application/implementation/event_handling/PLRunLoop/PLRunLoop_windows.h>

// Types
#include <core/PLTypes.h>

///////////////////////////////////////////////////////////////////////////////
#include <core/PLEventCenter.h>

///////////////////////////////////////////////////////////////////////////////
class PLWindow_windows : public IPLWindow, public IPLCompositeEventSource
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


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// =====================
	// *** Memory management
	PLWindow_windows(char *inName, PLRectange inFrame);
	virtual ~PLWindow_windows();


	// ===============================
	// *** [IMPLEMENTATION: IPLThread]
	virtual void show();
	virtual void getGLContext();
	virtual void setFocus();

	virtual PLRunLoop_windows *getRunLoop();


	// =============================================
	// *** [IMPLEMENTATION: IPLCompositeEventSource]
	virtual void initializeEnvironmentForEvent(PLEventKey *inoutEventKey);
};

#endif /* PLWINDOW_WINDOWS_H_ */
