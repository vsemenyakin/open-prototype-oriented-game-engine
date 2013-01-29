/*
 * PLAudioRecord.h
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */

#ifndef PLAUDIORECORD_H_
#define PLAUDIORECORD_H_

#include "../alutdlls36/alut.h"

#include "PLAudioObject.h"

///////////////////////////////////////////////////////////////////////////////
class PLAudioRecord : public PLAudioObject
{
private:
	ALuint _buffer;
	PLString _path;
	ALuint getBuffer(void);
public:
	friend class PLAudioSource;

	PLAudioRecord(void);
	PLAudioRecord(const PLString* inPath);
	virtual ~PLAudioRecord(void);

	void loadBufferFromFile(const PLString* inPath);
	void loadBufferHellowWorld(void);
	void clearBuffer(void);
};
///////////////////////////////////////////////////////////////////////////////
#endif /* PLAUDIORECORD_H_ */
