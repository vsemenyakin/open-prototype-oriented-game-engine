/*
 * PLAudioListener.h
 *
 *  Created on: 21.01.2013
 *      Author: ����
 */

#ifndef PLAUDIOLISTENER_H_
#define PLAUDIOLISTENER_H_

#include "../alutdlls36/alut.h"

#include "PLAudioObject.h"
///////////////////////////////////////////////////////////////////////////////
class PLAudioListener:public PLAudioObject
{
public:
	PLAudioListener();
	virtual ~PLAudioListener();
};

#endif /* PLAUDIOLISTENER_H_ */
