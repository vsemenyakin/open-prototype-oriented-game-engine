/*
 * PLAudioLibrary.h
 *
 *  Created on: 23.01.2013
 *      Author: нргл
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLAUDIOLIBRARY_H_
#define PLAUDIOLIBRARY_H_

///////////////////////////////////////////////////////////////////////////////
#include <map>

#include <core/PLString.h>

#include <alut.h>

#include "PLAudioObject.h"
#include "PLAudioRecord.h"

///////////////////////////////////////////////////////////////////////////////
class PLAudioLibrary: public PLAudioObject
{
private:
	std::map<PLString, PLAudioRecord*> _library;
public:
	PLAudioLibrary();
	virtual ~PLAudioLibrary();


	PLAudioRecord* getRecord(const PLString* inName);
	PLBOOL recordExist(const PLString* inName);
	void recordCreateAndLoadFromFile(const PLString* inPath,const PLString* inName);
	void recordLoadFromFile(const PLString* inPath, const PLString* inName);

	void recordCreateHelloWorld(const PLString* inName);
};

///////////////////////////////////////////////////////////////////////////////
#endif /* PLAUDIOLIBRARY_H_ */
