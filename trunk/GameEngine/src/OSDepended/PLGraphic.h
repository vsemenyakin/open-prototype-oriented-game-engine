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

#include "Implementation/Windows/PLGraphic_windows.h"

typedef PLWindow_windows PLWindow;

typedef PLRunLoop_windows PLRunLoop;
typedef PLKeyboardEventHandler_windows PLKeyboardEventHandler;

#endif


///////////////////////////////////////////////////////////////////////////////
// MAC_OS
#ifdef MAC_OS_X

#endif



#endif /* PLGRAPHIC_H_ */
