/*
 * IPLWindow.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLWINDOW_H_
#define IPLWINDOW_H_

///////////////////////////////////////////////////////////////////////////////
#include <application/interface/event_handling/IPLRunLoop.h>

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
class IPLWindow
{
public:
	virtual ~IPLWindow(){}

	virtual void show() = 0;
	virtual void getGLContext() = 0;
	virtual void setFocus() = 0;

	virtual IPLRunLoop *getRunLoop() = 0;

//	virtual void getGLContext();
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLWINDOW_H_ */
