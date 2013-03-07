/*
 * PLGraphic.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLGRAPHIC_H_
#define PLGRAPHIC_H_

///////////////////////////////////////////////////////////////////////////////
// WIN32
#ifdef WIN32

// TODO: Rename
#include "Implementation/Windows/PLGraphic_windows.h"

typedef PLApplication_windows PLApplication;

typedef PLThread_windows PLThread;
typedef PLRunLoop_windows PLRunLoop;
typedef PLKeyboardEventHandler_windows PLKeyboardEventHandler;

typedef PLWindow_windows PLWindow;

#endif


///////////////////////////////////////////////////////////////////////////////
// MAC_OS
#ifdef MAC_OS_X

#endif


#endif /* PLGRAPHIC_H_ */
