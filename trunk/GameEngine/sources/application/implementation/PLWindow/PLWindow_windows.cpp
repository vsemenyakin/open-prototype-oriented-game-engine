/*
 * PLWindow.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
// Note, you need to put an #include <windows.h> statement
// before the #include<GL/gl.h>.

// Header include
#include "PLWindow_windows.h"

// Utilities include
#include <map>

// OpenGL
//#include <gl/gl.h>
//#include <gl/glu.h>
#include "../../../OpenGL/PLShader.h"

// Logging
#include <iostream>

#include <application/implementation/multithreading/PLThread/PLThread_windows.h>

// Services
#include <application/implementation/event_handling/services_windows/PLWindowEventsService.h>

// Event handlers
#include <application/implementation/event_handling/services_windows/PLKeyboardEventHandler_windows.h>
#include <application/implementation/event_handling/services_windows/PLNonArgumentWindowEventHandler_windows.h>
#include <application/implementation/event_handling/services_windows/PLResizeWindowEventHandler_windows.h>
#include <application/implementation/event_handling/services_windows/PLWindowActivateEventHandler_windows.h>

// Event keys
#include <application/PLKeyboardEvents.h>
#include <application/PLWindowStateEvents.h>

///////////////////////////////////////////////////////////////////////////////
// | *********************** |
// | *** Window regestry *** |
// | *********************** |
///////////////////////////////////////////////////////////////////////////////
// *** Window registry data structure
static std::map<HWND, PLWindow_windows *> sWindowsAssigning;

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

///////////////////////////////////////////////////////////////////////////////
// | ************************ |
// | *** Window procedure *** |
// | ************************ |
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// | *********************** |
// | *** Window methods  *** |
// | *********************** |
///////////////////////////////////////////////////////////////////////////////
// *** Event management

PLWindow_windows::PLWindow_windows(char *inName, PLRectange inFrame)
	: _windowClass(NULL), _windowHandle(0), _name(inName), _frame(inFrame),
	  _runLoop(NULL)
{
}

PLWindow_windows::~PLWindow_windows()
{
	delete _windowClass;
}

///////////////////////////////////////////////////////////////////////////////
void PLWindow_windows::show()
{
	// Set run loop as current thread run loop
	_runLoop = (PLRunLoop_windows *)PLThread_windows::currentThread()->
			runLoop();

	PLWindowEventsService *theServiceWindowEventService =
			(PLWindowEventsService *)getRunLoop()->serviceForKey(
					kPLRunLoopServiceWindowEvent);
	if (NULL == theServiceWindowEventService) {
		getRunLoop()->addService(new PLWindowEventsService());
	}

	// Create and register windows class
	_windowClass = createWindowClass("openGL");

	// Create window
    _windowHandle = CreateWindowExA(
    		// Window extended style
    		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
    		"OpenGL",
    		_name,
    		// Required window style
    		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
    		(int)_frame.position.x,
    		(int)_frame.position.y,
    		(int)_frame.size.width,
    		(int)_frame.size.height,
			NULL,
			NULL,
			GetModuleHandleA(NULL),
			this);

    // Make map from window handle to window object
    assignWindowHandleWithWindowClass(_windowHandle, this);

    // OpenGL actions

	// Device context. The device context connects the window to the
	// GDI (Graphics Device Interface).
	HDC theDeviceContext = GetDC(_windowHandle);
	if (NULL == theDeviceContext)
	{
		std::cout << "Can't create a GL Device Context" << std::endl;
	}
	else
	{
		std::cout << theDeviceContext << std::endl;
	}

    // ***********************************
	// Set Pixel format
    setPixelFormat(theDeviceContext);

	// OpenGL program is linked to Rendering Context, that connects to device
	// context
	HGLRC theOpenGLRenderingContext = wglCreateContext(theDeviceContext);
	if(NULL == theOpenGLRenderingContext)
	{
		std::cout << "Can't create a openGL Rendering Context" << std::endl;
	}
	else
	{
		std::cout << theOpenGLRenderingContext << std::endl;
	}

	if(false == wglMakeCurrent(theDeviceContext, theOpenGLRenderingContext))
	{
		std::cout << "Can't set the context as current" << std::endl;
	}


	std::cout << "GL context created" << std::endl;
    // ***********************************

	ShowWindow(_windowHandle, SW_SHOW);
	SetForegroundWindow(_windowHandle);
	SetFocus(_windowHandle);
/*
	// RESIZE
	if (_frame.size.height == 0) // Prevent A Divide By Zero By
	{
		_frame.size.height = 1; // Making Height Equal One
	}

	// Reset The Current Viewport
	glViewport(0, 0 ,(GLsizei)_frame.size.width, (GLsizei)_frame.size.height);

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,
			(GLfloat)_frame.size.width/(GLfloat)_frame.size.height, 0.1f,
					100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

	// INIT_GL
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
*/
	// ****************************************
    GLenum theGlewInitializeError = glewInit();
    if (GLEW_OK != theGlewInitializeError)
    {
    	std::cout << "Glew started successfully" << std::endl;
    }

	// ****************************************
	const GLubyte *theOpnGLVersion = glGetString(GL_VERSION);
	std::cout << "OpenGL version: " << theOpnGLVersion << std::endl;

	const GLubyte *theShaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "Shader version: " << theShaderVersion << std::endl;

	const GLubyte *theVendorName = glGetString(GL_VENDOR);
	std::cout << "Vendor: " << theVendorName << std::endl;

	// Raw data buffers
	float thePositionData[] =
	{
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f
	};

//	float theColorData[] =
//	{
//		1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 1.0f
//	};

	// Create handlers to buffer objects
	GLuint theBufferObjectHandlers[2] = {0, 0};
	glGenBuffers(1, theBufferObjectHandlers);

	GLuint thePositionBufferHandler = theBufferObjectHandlers[0];
//	GLuint theColorBufferHandler = theBufferObjectHandlers[1];

	// Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, thePositionBufferHandler);
	glBufferData(GL_ARRAY_BUFFER, 9 + sizeof(float), thePositionData,
			GL_STATIC_DRAW);

//	glBindBuffer(GL_ARRAY_BUFFER, theColorBufferHandler);
//	glBufferData(GL_ARRAY_BUFFER, 9 + sizeof(float), theColorData,
//			GL_STATIC_DRAW);

	// Create and set the vertex array object
	GLuint theVertexArrayObjectHandler;

	glGenVertexArrays(1, &theVertexArrayObjectHandler);
	glBindVertexArray(theVertexArrayObjectHandler);

	// Map indexes to buffers
	glBindBuffer(GL_ARRAY_BUFFER, thePositionBufferHandler);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

//	glBindBuffer(GL_ARRAY_BUFFER, theColorBufferHandler);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	// Create shader
	const char *theVertexShaderCode = "#version 330\n"
								"in vec3 VertexPosition;\n"
//								"in vec3 VertexColor;\n"
								"out vec3 Color;\n"
								"out gl_PerVertex\n"
								"{\n"
								"\tvec4 gl_Position;\n"
								"};\n"
								"void main()\n"
								"{\n"
								"\tColor = vec3(1.0, 0.0, 0.0);\n"
								"\tgl_Position = vec4(0.5, 0.5, 0.5, 1.0);"
								"}\n\0";

	const char *theFragmentShaderCode = "#version 330\n"
								"in vec3 Color;\n"
								"out vec4 FragColor;\n"
								"void main()\n"
								"{\n"
								"\tFragColor = vec4(Color, 1.0);\n"
								"}\n\0";

	PLShader theShader;

	theShader.attachShader(PLShader::vertexShader, theVertexShaderCode);

	std::cout << " ----- " << std::endl;

	theShader.attachShader(PLShader::fragmentShader, theFragmentShaderCode);
	theShader.link();

	glUseProgram(theShader.handler());

	// Render array
	glBindVertexArray(theVertexArrayObjectHandler);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap buffers
	SwapBuffers(theDeviceContext);
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
	thePixelFormatDescriptor.cColorBits = 16;
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
	thePixelFormatDescriptor.cStencilBits = 16;
	thePixelFormatDescriptor.cAuxBuffers = 0; // Default
	thePixelFormatDescriptor.iLayerType = 0; // Default
	thePixelFormatDescriptor.bReserved = PFD_MAIN_PLANE;
	thePixelFormatDescriptor.dwLayerMask = 0; // Default
	thePixelFormatDescriptor.dwVisibleMask = 0; // Default
	thePixelFormatDescriptor.dwDamageMask = 0; // Default

	// Device context. The device context connects the window the
	// GDI (Graphics Device Interface).
	HDC theDeviceContext = GetDC(_windowHandle);
	if (NULL == theDeviceContext)
	{
		std::cout << "Can't create a GL Device Context" << std::endl;
	}
	else
	{
		std::cout << theDeviceContext << std::endl;
	}

	// Get nearest pixel format (gets by system based on requested device
	// context).
	int thePixelFormat = ChoosePixelFormat(theDeviceContext,
			&thePixelFormatDescriptor);
	if (0 == thePixelFormat)
	{
		std::cout << "Can't find suitable Pixel Format" << std::endl;
	}
	else
	{
		std::cout << thePixelFormat << std::endl;
	}

	if (false == SetPixelFormat(theDeviceContext, thePixelFormat,
			&thePixelFormatDescriptor))
	{
		std::cout << "Can't set the found Pixel Format" << std::endl;
	}

	// OpenGL program is linked to Rendering Context, that connects to device
	// context
	HGLRC theOpenGLRenderingContext = wglCreateContext(theDeviceContext);
	if(NULL == theOpenGLRenderingContext)
	{
		std::cout << "Can't create a openGL Rendering Context" << std::endl;
	}
	else
	{
		std::cout << theOpenGLRenderingContext << std::endl;
	}

	if(false == wglMakeCurrent(theDeviceContext, theOpenGLRenderingContext))
	{
		std::cout << "Can't set the context as current" << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
bool PLWindow_windows::setPixelFormat(HDC inDeviceContext)
{
	// TODO: Put here arguments for setting device context

	// Set Pixel format descriptor
	PIXELFORMATDESCRIPTOR thePixelFormatDescriptor;

	thePixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	thePixelFormatDescriptor.nVersion = 1;
	thePixelFormatDescriptor.dwFlags =
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	thePixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	thePixelFormatDescriptor.cColorBits = 32;
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
	thePixelFormatDescriptor.cDepthBits = 32; // Default
	thePixelFormatDescriptor.cStencilBits = 0;
	thePixelFormatDescriptor.cAuxBuffers = 0; // Default
	thePixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;
	thePixelFormatDescriptor.bReserved = 0; // Default
	thePixelFormatDescriptor.dwLayerMask = 0; // Default
	thePixelFormatDescriptor.dwVisibleMask = 0; // Default
	thePixelFormatDescriptor.dwDamageMask = 0; // Default

	// Get nearest pixel format (gets by system based on requested device
	// context).
	int thePixelFormat = ChoosePixelFormat(inDeviceContext,
			&thePixelFormatDescriptor);

	if (0 == thePixelFormat)
	{
		std::cout << "Can't find suitable Pixel Format" << std::endl;
		return false;
	}
	else
	{
		std::cout << thePixelFormat << std::endl;
	}

	if (false == SetPixelFormat(inDeviceContext, thePixelFormat,
			&thePixelFormatDescriptor))
	{
		std::cout << "Can't set the found Pixel Format" << std::endl;
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
WNDCLASSEX *PLWindow_windows::createWindowClass(const char *inName)
{
	WNDCLASSEX *theWindowClass = new WNDCLASSEX();

	// Size of structure
	theWindowClass->cbSize = sizeof(WNDCLASSEX);

	// Style of window. Redraw On Size, And Own DC For Window.
	theWindowClass->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Event handling procedure
	theWindowClass->lpfnWndProc = windowProcedure;

	// Extra bytes after window-class structure. Zero.
	theWindowClass->cbClsExtra = 0;

	// Extra bytes to allocate after the window instance. Zero.
	// the CLASS directive in resource file
	theWindowClass->cbWndExtra = 0;

	// Event handling procedure (window procedure)
	theWindowClass->hInstance = GetModuleHandleA(NULL);

	// Icon resource. If NULL - sets as default
	theWindowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// Handle to class cursor resource. If this is NULL,
	// an application must explicitly set the cursor shape whenever the mouse
	// moves into the application's window
	theWindowClass->hCursor = LoadCursor(NULL, IDC_ARROW);

	// Handle to class background brush. Sets color or brush to paint the
	// background.
	theWindowClass->hbrBackground = NULL; // No background

	// String that specifies the resource name of the class menu.
	theWindowClass->lpszMenuName = NULL; // Make no menu

	// Name of current class
	theWindowClass->lpszClassName = inName;

	// Small icon resource
	theWindowClass->hIconSm = NULL;

	ATOM theAtom = RegisterClassEx(theWindowClass);
	if (0 == theAtom)
    {
    	std::cout << "Failed to register the window class" << std::endl;

    	return NULL;
    }

	return theWindowClass;
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

///////////////////////////////////////////////////////////////////////////////
void PLWindow_windows::initializeEnvironmentForEvent(PLEventKey *inoutEventKey)
{
	PLWindowEventsService *theServiceWindowEventService =
			(PLWindowEventsService *)getRunLoop()->serviceForKey(
					kPLRunLoopServiceWindowEvent);
	if (NULL == theServiceWindowEventService) {
		getRunLoop()->addService(new PLWindowEventsService());
	}

	if (*inoutEventKey == kKeyDownEventKey)
	{
		theServiceWindowEventService->assignHandler(
				new PLKeyboardEventHandler_windows(
						WM_KEYDOWN, &kKeyDownEventKey, this));
	} else if (*inoutEventKey == kKeyUpEventKey)
	{
		theServiceWindowEventService->assignHandler(
				new PLKeyboardEventHandler_windows(
						WM_KEYUP, &kKeyUpEventKey, this));
	} else if (*inoutEventKey == kWindowActive ||
			*inoutEventKey == kWindowMinimize)
	{
		theServiceWindowEventService->assignWindowEvent(
				new PLWindowActivateEventHandler_windows(this));
	} else if (*inoutEventKey == kWindowShow)
	{
		theServiceWindowEventService->assignWindowEvent(
				new PLNonArgumentWindowEventHandler_windows(
						WM_SHOWWINDOW, &kWindowShow, this));
	} else if (*inoutEventKey == kWindowResize)
	{
		theServiceWindowEventService->assignWindowEvent(
				new PLResizeWindowEventHandler_windows(this));
	} else if (*inoutEventKey == kWindowClose)
	{
		theServiceWindowEventService->assignWindowEvent(
				new PLNonArgumentWindowEventHandler_windows(
						WM_CLOSE, &kWindowClose, this));
	}
}
