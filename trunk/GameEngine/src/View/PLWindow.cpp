/*
 * PLWindow.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
// Also, note that you'll need to put an #include <windows.h> statement
// before the #include<GL/gl.h>.

#include "PLWindow.h"

#include <iostream.h>
#include <gl/gl.h>
#include <gl/glu.h>

///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK windowProcedure(HWND inWindowHandle, UINT inMessage,
		WPARAM inWindowParameter, LPARAM inD)
{
	std::cout << "~~~" << std::endl;

	if (inMessage == WM_NCCREATE)
	{
		std::cout << "Window create message" << std::endl;
	}

	return DefWindowProc (inWindowHandle, inMessage, inWindowParameter, inD);
}

///////////////////////////////////////////////////////////////////////////////
PLWindow::PLWindow(char *inName, PLRectange inFrame)
{
	_name = inName;
	_frame = inFrame;
}

///////////////////////////////////////////////////////////////////////////////
void PLWindow::show()
{
	// *******************
	// Create window class
	// *******************
	_windowClass = new WNDCLASSEX();

	// Size of structure
	_windowClass->cbSize = sizeof(WNDCLASSEX);

	// Style of window
	_windowClass->style = CS_HREDRAW | CS_VREDRAW;

	// Event handling procedure
	_windowClass->lpfnWndProc = windowProcedure;

	// Extra bytes after window-class structure. Zero.
	_windowClass->cbClsExtra = 0;

	// Extra bytes to allocate after the window instance. Zero.
	// the CLASS directive in resource file
	_windowClass-> cbWndExtra = 0;

	// Event handling procedure (window procedure)
	_windowClass->hInstance = GetModuleHandleA(NULL);

	// Icon resource. If NULL - sets as default
	_windowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// Handle to class cursor resource. If this is NULL,
	// an application must explicitly set the cursor shape whenever the mouse
	// moves into the application's window
	_windowClass->hCursor = LoadCursor(NULL, IDC_ARROW);

	// Handle to class background brush. Sets color or brush to paint the
	// background.
	_windowClass->hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	// String that specifies the resource name of the class menu.
	_windowClass->lpszMenuName = NULL;

	// Name of current class
	_windowClass->lpszClassName = "OpenGL";

	// Small icon resource
	_windowClass->hIconSm = NULL;

	//////////////////////////////////////////
	ATOM theAtom;
	if (0 == (theAtom = RegisterClassEx(_windowClass)))
    {
    	///GetLastError()
    	std::cout << "Error" << std::endl;

    	return;
    }

    GetLastError();
    _window = CreateWindowExA(
    		WS_EX_APPWINDOW,
    		"OpenGL",
    		_name,
			WS_CLIPCHILDREN,
			100,
			100,
			500,
			500,
			NULL,
			NULL,
			GetModuleHandleA(NULL),
			this);

	// Show window
	ShowWindow(_window, SW_SHOW);
	UpdateWindow(_window);
}

PLWindow::~PLWindow()
{
	delete _windowClass;
}
