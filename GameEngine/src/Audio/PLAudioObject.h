/*
 * PLAudioObject.h
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLAUDIOOBJECT_H_
#define PLAUDIOOBJECT_H_

///////////////////////////////////////////////////////////////////////////////
#include "../Base/PLObject.h"
#include <alut.h>
#include "../Base/Diagnostic/IPLLogReceiver.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
class PLAudioObject : public PLObject
{
protected:
	void checkError(void);
	void clearErrors(void);

public:
	PLAudioObject();
	virtual ~PLAudioObject() = 0;
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLAUDIOOBJECT_H_ */
