/*
 * PLRunLoop.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLRunLoop_windows.h"

#include <iostream>

#include <gl/gl.h>
#include <gl/glu.h>

#include <wingdi.h>
#include <winuser.h>

///////////////////////////////////////////////////////////////////////////////
PLRunLoop_windows::PLRunLoop_windows()
	: _messageHandlersAssigning(), ___handle(0)
{
}

PLRunLoop_windows::~PLRunLoop_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLRunLoop_windows::assignHandler(IPLEventHandler *inHandler)
{
	PLHandlerRegistringInformation *theRegistringInformation =
			inHandler->getRegistringInformation();

	PLHandlerRegistringInformation::iterator theIterator =
			theRegistringInformation->begin();
	for (; theIterator != theRegistringInformation->end(); ++theIterator)
	{
		_messageHandlersAssigning[*theIterator] = inHandler;
	}
}

///////////////////////////////////////////////////////////////////////////////
void PLRunLoop_windows::run()
{
	bool theExecutingFlag = true;

	// -------------------------------------------------------------------
	// >>> INFORMATION
	// Event message contains next fields:
	// 1. HWND hwnd;		Window, that got the message
	// 2. UINT message;		Message code
	// 3. WPARAM wParam;	First message information
	// 4. LPARAM lParam;	Second message information
	// 5. DWORD time;		Time of message posting
	// 6. POINT pt;			Position of cursor when the message was posted
	//.
	// -------------------------------------------------------------------
	MSG theMessage;

	while (theExecutingFlag)
	{
		// --------------------------------------------------------------------
		// >>> INFORMATION
		// We use PeekMessage instead GetMessage function because the
		// GetMessage function wait in itself body until some message income,
		// and return some value only when the message income. In runloop makes
		// action but message processing needs, so we don't need this waiting
		//.
		// --------------------------------------------------------------------
		if (PeekMessage(&theMessage, NULL, 0, 0, PM_REMOVE))
		{
			if (theMessage.message == WM_QUIT)
			{
				 // Program received a quit message
				theExecutingFlag = false;
			}
			else
			{
				// ------------------------------------------------------------
				// >>> INFORMATION
				// Next to lines needs to process message with user handlers.
				// We get the handler that process message with got code from
				// message handlers assigning object
				//.
				// -----------------------------------------------------------
				if (_messageHandlersAssigning.end() !=
						_messageHandlersAssigning.find(theMessage.message))
				{
					((IPLEventHandler_windows *)
							_messageHandlersAssigning[theMessage.message])->
									handleEvent(theMessage);
				}

				// ------------------------------------------------------------
				// >>> INFORMATION
				// Next to lines needs to send message to thread's window. The
				// DispatchMessage function .
				//.
				// -----------------------------------------------------------
				TranslateMessage(&theMessage);
				DispatchMessage(&theMessage);
			}
		}
		else
		{
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
//			glLoadIdentity();									// Reset The Current Modelview Matrix
//			glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
//			glBegin(GL_TRIANGLES);								// Drawing Using Triangles
//				glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
//				glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left
//				glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
//			glEnd();											// Finished Drawing The Triangle
//			glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
//			glBegin(GL_QUADS);									// Draw A Quad
//				glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
//				glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
//				glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
//				glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
//			glEnd();
//
//			SwapBuffers(___handle);

			// No events got on this runloop iteration.
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//void PLRunLoop_windows::setHandle(HDC inHandle)
//{
//	___handle = inHandle;
//}

///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK PLRunLoop_windows::windowProcedure(HWND inWindowHandle,
		UINT inMessage, WPARAM inWindowParameter, LPARAM inD)
{
	switch (inMessage)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(inWindowParameter))					// Check Minimization State
			{
			}
			else
			{
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:
		{
			switch (inWindowParameter)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	return DefWindowProc(inWindowHandle, inMessage, inWindowParameter, inD);
}
