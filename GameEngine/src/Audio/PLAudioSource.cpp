/*
 * PLAudioSource.cpp
 *
 *  Created on: 21.01.2013
 *      Author: нргл
 */

#include "PLAudioSource.h"
#include "PLAudioController.h"

///////////////////////////////////////////////////////////////////////////////
PLAudioSource::PLAudioSource()
{
	PLAudioObject::clearErrors();

	alGenSources(1, &_source);

	PLAudioObject::clearErrors();

	ALfloat sourcePosition[] = {1.0,0.0,0.0};
	ALfloat sourceVelocity[] = {0.0,0.0,0.0};

	alSourcef(_source, AL_PITCH, 1.0f);
	alSourcef(_source, AL_GAIN, 1.0f);
	alSourcei(_source, AL_LOOPING, AL_TRUE);
	alSourcefv(_source, AL_POSITION, sourcePosition);
	alSourcefv(_source, AL_VELOCITY, sourceVelocity);

	PLAudioObject::checkError();
}

PLAudioSource::~PLAudioSource()
{
	PLAudioObject::clearErrors();

	alDeleteSources(1, &_source);

	PLAudioObject::checkError();
}
///////////////////////////////////////////////////////////////////////////////
void PLAudioSource::attachAudio(const PLString* inName)
{
	PLAudioObject::clearErrors();
	PLAudioController* theAudioController = PLAudioController::instance();
	PLAudioRecord* theRecord = theAudioController->_audioLibrary.getRecord(inName);

	if(theAudioController->_audioLibrary.recordExist(inName))
	{
		alSourcei(_source, AL_BUFFER, theRecord->getBuffer());
	}

	PLAudioObject::checkError();
};

void PLAudioSource::play()
{
	PLAudioObject::clearErrors();
	alSourcePlay(_source);
	PLAudioObject::checkError();
};

void PLAudioSource::stop()
{
	PLAudioObject::clearErrors();
	alSourceStop(_source);
	PLAudioObject::checkError();
};

void PLAudioSource::pause()
{
	PLAudioObject::clearErrors();
	alSourcePause(_source);
	PLAudioObject::checkError();
};
