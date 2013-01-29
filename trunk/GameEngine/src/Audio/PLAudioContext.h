/*
 * PLAudioContext.h
 *
 *  Created on: 17.01.2013
 *      Author: нргл
 */

#ifndef PLAUDIOCONTEXT_H_
#define PLAUDIOCONTEXT_H_

#include <map>

#include "../Base/PLString.h"
#include "../alutdlls36/alut.h"

#include "PLAudioObject.h"
#include "PLAudioListener.h"
#include "PLAudioSource.h"
///////////////////////////////////////////////////////////////////////////////
class PLAudioContext: public PLAudioObject
{
private:
	ALCcontext* _context;
	PLAudioListener _listener;
	std::map<PLString, PLAudioSource*> _sources;

public:
	ALCcontext* getContext(void);

	PLAudioContext(ALCdevice* inDevice, ALCint* inAttributes);
	virtual ~PLAudioContext(void);

	PLAudioSource* getSource(const PLString* inName);
	void createSource(const PLString* inName);
	void destroySource(const PLString* inName);
	PLBOOL sourceExist(const PLString* inName);
};
///////////////////////////////////////////////////////////////////////////////
#endif /* PLAUDIOCONTEXT_H_ */
