/*
 * PLEmptyReflector.h
 *
 *  Created on: Dec 29, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef PLEMPTYREFLECTOR_H_
#define PLEMPTYREFLECTOR_H_

///////////////////////////////////////////////////////////////////////////////
#include "IPLCharacterReflector.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterReflector;

///////////////////////////////////////////////////////////////////////////////
class PLEmptyReflector : public IPLCharacterReflector
{
private:
	PLCharacterReflector *_wrappedReflector;

public:
	PLEmptyReflector();
	virtual ~PLEmptyReflector();

	// ----------------------------------------------------
	// *** Updating [IMPLEMENTATION: IPLCharacterReflector]
	virtual PLCharacterReflectorUpdatingResult *updateForRootIteratorWithSymbol(
			PLReflectionTree::node_iterator *inIterator,
					PLCharacter inCharacter);

	virtual PLCharacterReflectorUpdatingResult *updateWithSymbol(
			PLCharacter inCharacter);

	// ----------------------------------------------------
	// *** Base behavior [IMPLEMENTATION: PLObject]
	virtual PLString *description();
};

#endif /* PLEMPTYREFLECTOR_H_ */
