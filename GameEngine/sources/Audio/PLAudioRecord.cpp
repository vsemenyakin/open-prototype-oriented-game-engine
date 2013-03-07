/*
 * PLAudioRecord.cpp
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */

#include "PLAudioRecord.h"

PLAudioRecord::PLAudioRecord(void)
{
	_buffer = 0;
}

PLAudioRecord::PLAudioRecord(const PLString* inPath)
{
	_buffer = 0;
	loadBufferFromFile(inPath);
}

PLAudioRecord::~PLAudioRecord()
{
	clearBuffer();
}
///////////////////////////////////////////////////////////////////////////////
void PLAudioRecord::loadBufferFromFile(const PLString* inPath)
{
	clearBuffer();

	PLAudioObject::clearErrors();

	_path = inPath->getCString();
	_buffer = alutCreateBufferFromFile(inPath->getCString());

	PLAudioObject::checkError();
}

void PLAudioRecord::loadBufferHellowWorld(void)
{
	clearBuffer();

	PLAudioObject::clearErrors();

	_buffer = alutCreateBufferHelloWorld();

	PLAudioObject::checkError();
}

void PLAudioRecord::clearBuffer(void)
{
	if(_buffer)
	{
		PLAudioObject::clearErrors();

		alDeleteBuffers(1, &_buffer);

		PLAudioObject::checkError();
	}
}

ALuint PLAudioRecord::getBuffer(void)
{
	return _buffer;
};
