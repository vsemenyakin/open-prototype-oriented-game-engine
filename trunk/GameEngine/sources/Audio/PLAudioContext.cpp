/*
 * PLAudioContext.cpp
 *
 *  Created on: 17.01.2013
 *      Author: нргл
 */

#include "PLAudioContext.h"
#include "PLAudioController.h"
#include "PLAudioRecord.h"
///////////////////////////////////////////////////////////////////////////////
PLAudioContext::PLAudioContext(ALCdevice* inDevice, ALCint* inAttributes)
{
	PLAudioObject::clearErrors();

	_context = alcCreateContext(inDevice, inAttributes);

	PLAudioObject::checkError();
}

PLAudioContext::~PLAudioContext(void)
{
	if(_context)
	{
	PLAudioObject::clearErrors();

	alcDestroyContext(_context);

	PLAudioObject::checkError();
	}
}
///////////////////////////////////////////////////////////////////////////////
ALCcontext* PLAudioContext::getContext(void)
{
	return _context;
};

void PLAudioContext::createSource(const PLString* inName)
{
	if(sourceExist(inName) == false)
	{
		PLAudioSource* theAudioSource = new PLAudioSource();
		_sources[*inName] = theAudioSource;
	}
};

void PLAudioContext::destroySource(const PLString* inName)
{
	if(sourceExist(inName) == true)
	{
		delete _sources[*inName];
		_sources.erase(*inName);
	}
};

PLBOOL PLAudioContext::sourceExist(const PLString* inName)
{
	if(_sources.find(*inName) != _sources.end())
	{
		return true;
	}
	else
	{
		return false;
	}
};

PLAudioSource* PLAudioContext::getSource(const PLString* inName)
{
	if(sourceExist(inName) == true)
	{
		return _sources[*inName];
	}
	else
	{
		return NULL;
	}
};
