/*
 * PLStringReflector.h
 *
 *  Created on: Jan 2, 2013
 *      Author: Admin
 */

#ifndef PLSTRINGREFLECTOR_H_
#define PLSTRINGREFLECTOR_H_

///////////////////////////////////////////////////////////////////////////////
#include "IPLCharacterReflector.h"

#include <map>
#include "../../Base/PLString.h"

///////////////////////////////////////////////////////////////////////////////
class PLStringReflector : public IPLCharacterReflector
{
private:
	PLString _string;

	struct
	{
		size_t index;
		PLReflectionTree::node_iterator *root;
	} typedef PLGrowPoint;


	std::map<PLReflectionTree::node_iterator *, PLGrowPoint *> _updatedIndexes;

public:
	PLStringReflector(PLString *inString);
	virtual ~PLStringReflector();

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

#endif /* PLSTRINGREFLECTOR_H_ */
