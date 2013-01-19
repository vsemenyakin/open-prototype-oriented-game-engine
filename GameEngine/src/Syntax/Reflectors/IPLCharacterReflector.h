/*
 * PLCharacterReflector.h
 *
 *  Created on: Oct 22, 2012
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef IPLCHARACTERREFLECTOR_H_
#define IPLCHARACTERREFLECTOR_H_

#include "../../Base/PLCore.h"

#include "../../CoreCollections/PL_core_graph.h"

#include "../../Behavior/Reflection/PLReflection.h"
#include "../../Behavior/PLInstaller.h"

#include <list.h>

///////////////////////////////////////////////////////////////////////////////
enum
{
	PLCharacterReflectorUpdating,
	PLCharacterReflectorFinished,
	PLCharacterReflectorFailed,
	PLCharacterReflectorFinal // For special cases only
} typedef PLReflectorUpdateStatus;

///////////////////////////////////////////////////////////////////////////////
// Types
typedef PLIndex PLBranchIndex;

typedef PL_core_graph<PLReflection *, void *> PLReflectionTree;
typedef list<PLReflectionTree::node_iterator *> PLReflectionTreeIterationFront;

///////////////////////////////////////////////////////////////////////////////
struct
{
	PLReflectorUpdateStatus updateStatus;
	PLReflectionTree::node_iterator *root;
	PLReflectionTreeIterationFront *branches;
} typedef PLCharacterReflectorUpdatingResult;

///////////////////////////////////////////////////////////////////////////////
class IPLCharacterReflector : public PLObject
{
public:
	// Public update
	virtual PLCharacterReflectorUpdatingResult *updateWithSymbol(
			PLCharacter inCharacter) = 0;

	// Protected update
	virtual PLCharacterReflectorUpdatingResult *updateForRootIteratorWithSymbol
			(PLReflectionTree::node_iterator *inIterator,
					PLCharacter inCharacter) = 0;

	// Description
	virtual PLString *description()
	{
		return new PLString("IPLCharacterReflector\0");
	}
};

#endif /* IPLCHARACTERREFLECTOR_H_ */
