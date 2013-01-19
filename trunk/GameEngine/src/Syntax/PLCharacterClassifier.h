/*
 * PLCharacterClassifier.h
 *
 *  Created on: 07.09.2012
 *      Author: Сергей
 */

#ifndef PLCHARACTERCLASSIFIER_H_
#define PLCHARACTERCLASSIFIER_H_

///////////////////////////////////////////////////////////////////////////////
#include <list.h>
#include "PLCharacterSet.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterClassifier
{
	std::list<void *> **_hashBuffer;
	std::list<void *> *_defaultObjects;

public:
	PLCharacterClassifier();
	virtual ~PLCharacterClassifier();

	void setDefaultObject(void *inObject);

	void setObjectForCharacterSet(PLCharacterSet *inSet, void *inObject);
	std::list<void *> *objectsForCharacter(char inCharacter);
};

#endif /* PLCHARACTERCLASSIFIER_H_ */
