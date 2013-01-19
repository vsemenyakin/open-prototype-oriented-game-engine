/*
 * PLReflection.h
 *
 *  Created on: 13.10.2012
 *      Author: Сергей
 */

#ifndef PLREFLECTION_H_
#define PLREFLECTION_H_

///////////////////////////////////////////////////////////////////////////////
typedef void (PLCallback)(void *inTarget, void *inArgument);

///////////////////////////////////////////////////////////////////////////////
class PLReflection
{
private:


	// **************************************************************
	// *					Private _ Variables						*
	// **************************************************************

	// ---------------
	// *** Callback
	PLCallback *_callback;

	// ----------------------
	// *** Callback arguments
	void *_target;
	void *_argument;

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLReflection(void *inTarget, PLCallback *inCallback);
	PLReflection(PLReflection *inReflection, void *inArgument);

	virtual ~PLReflection();

	// -----------
	// *** Calling

	void setArgument(void *inArgument);
	void *getArgument();

	void call();

	// ------------------
	// *** Static members
	static PLReflection *dummyReflection();
};

#endif /* PLREFLECTION_H_ */
