/*
 * PLWindow.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
// Also, note that you'll need to put an #include <windows.h> statement
// before the #include<GL/gl.h>.

#include "PLWindow_windows.h"

#include <iostream.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <map.h>

///////////////////////////////////////////////////////////////////////////////
// | *********************** |
// | *** Window regestry *** |
// | *********************** |
///////////////////////////////////////////////////////////////////////////////
// *** Window registry
static map<HWND, PLWindow_windows *> sWindowsAssigning;

// -----------------------------------------------------
// *** Assigning window class and window handle function
void assignWindowHandleWithWindowClass(HWND inWindowHandle,
		PLWindow_windows *inWindowClass)
{
	sWindowsAssigning[inWindowHandle] = inWindowClass;
}

// -----------------------
// *** Window class access
PLWindow_windows *getWindowClassByWindowHandle(HWND inWindowHandle)
{
	return sWindowsAssigning[inWindowHandle];
}

// ---------------------
// *** Windows procedure
LRESULT CALLBACK windowProcedure(HWND inWindowHandle, UINT inMessage,
		WPARAM inWindowParameter, LPARAM inD)
{
	PLWindow_windows *theWindows =
			getWindowClassByWindowHandle(inWindowHandle);
	if (NULL != theWindows)
	{
		// Delegating for created window
		return theWindows->getRunLoop()->windowProcedure(inWindowHandle,
				inMessage, inWindowParameter, inD);
	}

	// Default call
	return DefWindowProc(inWindowHandle, inMessage, inWindowParameter, inD);
}


///////////////////////////////////////////////////////////////////////////////
// | *********************** |
// | *** Window methods  *** |
// | *********************** |
///////////////////////////////////////////////////////////////////////////////
// *** Event management
PLWindow_windows::PLWindow_windows(char *inName, PLRectange inFrame)
{
	_name = inName;
	_frame = inFrame;
}

PLWindow_windows::~PLWindow_windows()
{
	delete _windowClass;
}

///////////////////////////////////////////////////////////////////////////////
void PLWindow_windows::show()
{
	_runLoop = new PLRunLoop_windows();

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

    _windowHandle = CreateWindowExA(
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

    assignWindowHandleWithWindowClass(_windowHandle, this);

	// Show window
    this->getGLContext();

	ShowWindow(_windowHandle, SW_SHOW);
	UpdateWindow(_windowHandle);

	// RESIZE
	int width = 500;
	int height = 500;

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

	// INIT_GL
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// DRAW_SCENE
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();
}

///////////////////////////////////////////////////////////////////////////////
void PLWindow_windows::getGLContext()
{
	// Set Pixel forma descriptor
	PIXELFORMATDESCRIPTOR thePixelFormatDescriptor;

	thePixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	thePixelFormatDescriptor.nVersion = 1;
	thePixelFormatDescriptor.dwFlags =
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	thePixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	thePixelFormatDescriptor.cColorBits = 24;
	thePixelFormatDescriptor.cRedBits = 0; // Default
	thePixelFormatDescriptor.cRedShift = 0; // Default
	thePixelFormatDescriptor.cGreenBits = 0; // Default
	thePixelFormatDescriptor.cGreenShift = 0; // Default
	thePixelFormatDescriptor.cBlueBits = 0; // Default
	thePixelFormatDescriptor.cBlueShift = 0; // Default
	thePixelFormatDescriptor.cAlphaBits = 0; // Default
	thePixelFormatDescriptor.cAlphaShift = 0; // Default
	thePixelFormatDescriptor.cAccumBits = 0; // Default
	thePixelFormatDescriptor.cAccumRedBits = 0; // Default
	thePixelFormatDescriptor.cAccumGreenBits = 0; // Default
	thePixelFormatDescriptor.cAccumBlueBits = 0; // Default
	thePixelFormatDescriptor.cAccumAlphaBits = 0; // Default
	thePixelFormatDescriptor.cDepthBits = 0; // Default
	thePixelFormatDescriptor.cStencilBits = 32;
	thePixelFormatDescriptor.cAuxBuffers = 0; // Default
	thePixelFormatDescriptor.iLayerType = 0; // Default
	thePixelFormatDescriptor.bReserved = PFD_MAIN_PLANE;
	thePixelFormatDescriptor.dwLayerMask = 0; // Default
	thePixelFormatDescriptor.dwVisibleMask = 0; // Default
	thePixelFormatDescriptor.dwDamageMask = 0; // Default

	RECT theWindowRectange;
	GetClientRect(_windowHandle, &theWindowRectange);

	std::cout << theWindowRectange.left << " " << theWindowRectange.right <<
			" " << theWindowRectange.top << " " << theWindowRectange.bottom <<
					std::endl;

	// Device context. The device context connects the window the
	// GDI (Graphics Device Interface).
	HDC theDeviceContext = GetDC(_windowHandle);

	// Get nearest pixel format (gets by system based on requested device
	// context).
	int thePixelFormat = ChoosePixelFormat(theDeviceContext,
			&thePixelFormatDescriptor);

	SetPixelFormat(theDeviceContext, thePixelFormat,
			&thePixelFormatDescriptor);

	// OpenGL program is linked to Rendering Context, that connects to device
	// context
	HGLRC theOpenGLRenderingContext = wglCreateContext(theDeviceContext);
	if(theOpenGLRenderingContext == NULL)
	{
		std::cout << "Handle wasn't created" << std::endl;
	}

	if(wglMakeCurrent(theDeviceContext, theOpenGLRenderingContext) == false)
	{
		std::cout << "Handle wasn't created" << std::endl;
	}

	//
	wglMakeCurrent(theDeviceContext, theOpenGLRenderingContext);
}

///////////////////////////////////////////////////////////////////////////////
PLRunLoop_windows *PLWindow_windows::getRunLoop()
{
	return _runLoop;
}

///////////////////////////////////////////////////////////////////////////////
void PLWindow_windows::setFocus()
{
	SetFocus(_windowHandle);
}
