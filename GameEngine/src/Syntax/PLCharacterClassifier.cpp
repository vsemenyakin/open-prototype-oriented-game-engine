/*
 * PLCharacterClassifier.cpp
 *
 *  Created on: 07.09.2012
 *      Author: Сергей
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterClassifier.h"

///////////////////////////////////////////////////////////////////////////////
PLCharacterClassifier::PLCharacterClassifier()
	: _hashBuffer(NULL), _defaultObjects(NULL)
{
	_hashBuffer = new std::list<void *> *[256];
	for (int theIndex = 0; theIndex < 256; ++theIndex)
	{
		_hashBuffer[theIndex] = _defaultObjects;
	}
}

PLCharacterClassifier::~PLCharacterClassifier()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterClassifier::setDefaultObject(void *inObject)
{
	if (NULL == _defaultObjects)
	{
		_defaultObjects = new std::list<void *>();
	}

	_defaultObjects->push_back(inObject);
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterClassifier::setObjectForCharacterSet(PLCharacterSet *inSet,
		void *inObject)
{
	for (int theCharacterCode = 0; theCharacterCode < 256; ++theCharacterCode)
	{
		if (inSet->containsCharacter(theCharacterCode))
		{
			std::list<void *> *theObjects = _hashBuffer[theCharacterCode];
			theObjects->push_back(inObject);
		}
	}
}

std::list<void *> *PLCharacterClassifier::objectsForCharacter(char inCharacter)
{
	std::list<void *> *theKeyPointer = _hashBuffer[inCharacter];
	return theKeyPointer;
}
