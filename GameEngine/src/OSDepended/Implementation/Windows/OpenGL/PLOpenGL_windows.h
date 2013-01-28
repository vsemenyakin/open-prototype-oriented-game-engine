/*
 * PLOpenGL_windows.h
 *
 *  Created on: Jan 25, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLOPENGL_WINDOWS_H_
#define PLOPENGL_WINDOWS_H_

///////////////////////////////////////////////////////////////////////////////
#include "../../../Interface/OpenGL/PLOpenGLContext_interface.h"

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
class PLOpenGL_windows : public PLOpenGLContext_interface
{
private:


public:
	PLOpenGL_windows();
	virtual ~PLOpenGL_windows();
};

#endif /* PLOPENGL_WINDOWS_H_ */
