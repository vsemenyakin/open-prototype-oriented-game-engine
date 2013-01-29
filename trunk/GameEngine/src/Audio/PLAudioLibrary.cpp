/*
 * PLAudioLibrary.cpp
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */

#include "PLAudioLibrary.h"

PLAudioLibrary::PLAudioLibrary() {
	// TODO Auto-generated constructor stub

}

PLAudioLibrary::~PLAudioLibrary() {
	// TODO Auto-generated destructor stub
}
///////////////////////////////////////////////////////////////////////////////
void PLAudioLibrary::recordCreateAndLoadFromFile(const PLString* inPath, const PLString* inName)
{
	PLAudioRecord* theRecord = new PLAudioRecord(inPath);
	_library[*inName] = theRecord;
};

void PLAudioLibrary::recordLoadFromFile(const PLString* inPath, const PLString* inName)
{
	PLAudioRecord* theRecord = new PLAudioRecord(inPath);
	if(_library[*inName])
	{
		delete _library[*inName];
		_library[*inName] = theRecord;
	}

};

void PLAudioLibrary::recordCreateHelloWorld(const PLString* inName)
{
	PLAudioRecord* theRecord = new PLAudioRecord();
	theRecord->loadBufferHellowWorld();
	_library[*inName] = theRecord;
};

PLBOOL PLAudioLibrary::recordExist(const PLString* inName)
{
	if(_library.find(*inName) != _library.end())
	{
		return true;
	}
	else
	{
		return false;
	}
};

PLAudioRecord* PLAudioLibrary::getRecord(const PLString* inName)
{
	return _library[*inName];
}
