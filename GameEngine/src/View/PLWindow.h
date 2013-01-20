/*
 * PLWindow.h
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

#ifndef PLWINDOW_H_
#define PLWINDOW_H_

///////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#include "../Base/PLCore.h"

///////////////////////////////////////////////////////////////////////////////
class PLWindow
{
private:

	// Low level properties
	WNDCLASSEX *_windowClass;
	HWND _window;

	// High level properties
	char *_name;
	PLRectange _frame;

	/////////////////


public:
	PLWindow(char *inName, PLRectange inFrame);
	virtual ~PLWindow();

	void show();
};

#endif /* PLWINDOW_H_ */
