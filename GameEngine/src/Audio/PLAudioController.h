/*
 * PLAudioDevice.h
 *
 *  Created on: 17.01.2013
 *      Author: нргл
 */
#ifndef PLAUDIODEVICE_H_
#define PLAUDIODEVICE_H_

#include <map>

#include "../Base/PLString.h"
#include "../alutdlls36/alut.h"

#include "PLAudioObject.h"
#include "PLAudioContext.h"
#include "PLAudioLibrary.h"
///////////////////////////////////////////////////////////////////////////////
class PLAudioController : public PLAudioObject
{
private:
	ALCdevice* _device;
	std::map<PLString, PLAudioContext*> _contexts;
protected:
	PLAudioController();
public:
	PLAudioLibrary _audioLibrary;

	static PLAudioController*  instance();
	virtual ~PLAudioController();

	void initialiseDevice(const PLString* inName);

	PLBOOL contextExist(const PLString* inName);
	void createContext(const PLString* inName, ALCint* inAttributes);
	void destroyContext(const PLString* inName);
	void setContextCurrent(const PLString* inName);
	PLAudioContext* getContext(const PLString* inName);

};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLAUDIODEVICE_H_ */
