/*
 * PLThread_interface.h
 *
 *  Created on: Jan 24, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLTHREAD_INTERFACE_H_
#define PLTHREAD_INTERFACE_H_

///////////////////////////////////////////////////////////////////////////////
typedef void (PLThreadEnterPointFunction)(void *);

///////////////////////////////////////////////////////////////////////////////
class PLThread_interface
{
public:
	virtual void runWithArgument(void *inArgument) = 0;
};

#endif /* PLTHREAD_INTERFACE_H_ */
