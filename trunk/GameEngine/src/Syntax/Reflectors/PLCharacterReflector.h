/*
 * PLCharacterReflector.h
 *
 *  Created on: Oct 22, 2012
 *      Author: Admin
 */

#ifndef PLCHARACTERREFLECTOR_H_
#define PLCHARACTERREFLECTOR_H_
///////////////////////////////////////////////////////////////////////////////
#include "IPLCharacterReflector.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterSet;
class PLReflection;

///////////////////////////////////////////////////////////////////////////////
class PLCharacterReflector : public IPLCharacterReflector
{
private:
	PLCharacterSet *_set;
	PLReflection *_reflection;

	map<PLReflectionTree::node_iterator *, PLReflection *> _updatedIterators;

public:


	// **************************************************************
	// *					Public _ Methods						*
	// **************************************************************

	// ---------------------
	// *** Memory management
	PLCharacterReflector(PLCharacterSet *inSet, PLReflection *inReflection);
	virtual ~PLCharacterReflector();

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

#endif /* PLCHARACTERREFLECTOR_H_ */
