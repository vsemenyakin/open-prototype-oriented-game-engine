/*
 * PLAudioSource.h
 *
 *  Created on: 21.01.2013
 *      Author: нргл
 */

#ifndef PLAUDIOSOURCE_H_
#define PLAUDIOSOURCE_H_

#include "../alutdlls36/alut.h"

#include "PLAudioObject.h"
///////////////////////////////////////////////////////////////////////////////
class PLAudioSource: public PLAudioObject
{
private:
	ALuint _source;
	ALuint getSource(void);
public:
	PLAudioSource();
	virtual ~PLAudioSource();

	void attachAudio(const PLString* inName);

	void play(void);
	void stop(void);
	void pause(void);

};

#endif /* PLAUDIOSOURCE_H_ */
