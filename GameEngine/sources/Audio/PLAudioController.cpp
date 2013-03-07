/*
 * PLAudioDevice.cpp
 *
 *  Created on: 17.01.2013
 *      Author: нргл
 */

#include "PLAudioController.h"
using namespace std;
///////////////////////////////////////////////////////////////////////////////
PLAudioController::PLAudioController()
{
	alutInit(NULL, NULL);
}

PLAudioController::~PLAudioController()
{
	alutExit();
}

static PLAudioController* sAudioController = NULL;

PLAudioController* PLAudioController::instance()
{
	if(sAudioController == NULL)
	{
		sAudioController = new PLAudioController();
	};
	return sAudioController;
}
///////////////////////////////////////////////////////////////////////////////
void PLAudioController::initialiseDevice(const PLString* inName)
{
	PLAudioObject::clearErrors();
	if(inName != NULL)
	{
		_device = alcOpenDevice((const ALCchar*)inName->getCString());
	}
	else
	{
		_device = alcOpenDevice(NULL);
	}
	PLAudioObject::checkError();
};

void PLAudioController::createContext(const PLString* inName, ALCint* inAttributes)
{
	if(contextExist(inName) == false)
	{
		PLAudioObject::clearErrors();

		PLAudioContext* theContext = new PLAudioContext(_device, inAttributes);
		_contexts[*inName] = theContext;

		PLAudioObject::checkError();

		ALfloat listenerPosition[] = {0.0,0.0,0.0};
		ALfloat listenerVelocity[] = {0.0,0.0,0.0};
		ALfloat listenerOrientation[] = {0.0,0.0,-1.0, 0.0,1.0,0.0};

		alListenerfv(AL_POSITION, listenerPosition);
		alListenerfv(AL_VELOCITY, listenerVelocity);
		alListenerfv(AL_ORIENTATION, listenerOrientation);

		PLAudioObject::checkError();
	};
};

void PLAudioController::destroyContext(const PLString* inName)
{
	if(contextExist(inName) == true)
	{
		delete _contexts[*inName];
		_contexts.erase(*inName);
	}
	else
	{
		//
	}
};

void PLAudioController::setContextCurrent(const PLString* inName)
{
	PLAudioObject::clearErrors();

	if(contextExist(inName) == true)
	{
		alcMakeContextCurrent(_contexts[*inName]->getContext());

		PLAudioObject::checkError();
	}
	else
	{
		//
	}
};

PLBOOL PLAudioController::contextExist(const PLString* inName)
{
	if(_contexts.find(*inName) != _contexts.end())
	{
		return true;
	}
	else
	{
		return false;
	}
};

PLAudioContext* PLAudioController::getContext(const PLString* inName)
{
	if(contextExist(inName) == true)
	{
		return _contexts[*inName];
	}
	else
	{
		return NULL;
	}
};
