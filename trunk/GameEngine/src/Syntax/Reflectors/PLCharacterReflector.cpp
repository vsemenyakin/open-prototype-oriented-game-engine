/*
 * PLCharacterReflector.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterReflector.h"
#include "../PLCharacterSet.h"
#include "../../CoreCollections/PL_core_pool.h" // For PLPoolDefaultKey

#include "../../Base/Diagnostic/PLScopeBasedLog.h"

///////////////////////////////////////////////////////////////////////////////
// *** Memory management
///////////////////////////////////////////////////////////////////////////////

PLCharacterReflector::PLCharacterReflector(PLCharacterSet *inSet,
		PLReflection *inReflection)
{
	_set = inSet;
	_reflection = inReflection;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterReflector::~PLCharacterReflector()
{
}

///////////////////////////////////////////////////////////////////////////////
// *** Updating [IMPLEMENTATION: IPLCharacterReflector]
///////////////////////////////////////////////////////////////////////////////
PLCharacterReflectorUpdatingResult *PLCharacterReflector::updateWithSymbol(
		PLCharacter inCharacter)
{
	return updateForRootIteratorWithSymbol(NULL, inCharacter);
}

PLCharacterReflectorUpdatingResult *PLCharacterReflector::
		updateForRootIteratorWithSymbol(
				PLReflectionTree::node_iterator *inIterator,
						PLCharacter inCharacter)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print("Updating reflector ");
	PLScopeBasedLog::sharedLog()->print(
			(char *)this->description()->getCString());
	PLScopeBasedLog::sharedLog()->print(" with character \'");
	PLScopeBasedLog::sharedLog()->print(inCharacter);
	PLScopeBasedLog::sharedLog()->print("\'");

	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	// Create update
	PLCharacterReflectorUpdatingResult *theResult =
			new PLCharacterReflectorUpdatingResult();

	// By default return status is finished
	theResult->updateStatus = PLCharacterReflectorFailed;

	// If this iterator wasn't iterated firstly...
	if (_updatedIterators.find(inIterator) != _updatedIterators.end())
	{
		// . ~~~~
		PLScopeBasedLog::sharedLog()->print(
				"Reflector was updated for current iterator.");
		PLScopeBasedLog::sharedLog()->endLine();
		// . ~~~~

		theResult->updateStatus = PLCharacterReflectorFinished;
		theResult->root = PLReflectionTree::sharedGraph()->
				createNodeWithValue(PLReflection::dummyReflection());

		// Test for condition - if the reflector has reflection
		PLReflection *theReflection = _updatedIterators[inIterator];
		if (NULL != theReflection)
		{
			theResult->root->createNextNodeWithValue(
					_updatedIterators[inIterator], NULL);

			theResult->branches = new PLReflectionTreeIterationFront();
			theResult->branches->push_back((*theResult->root->edgesOut()->
					begin())->iteratorOut());

			// . ~~~~
			PLScopeBasedLog::sharedLog()->print(
					"Created one reflection branch (reflection: ");
			PLScopeBasedLog::sharedLog()->print(_updatedIterators[inIterator]);
			PLScopeBasedLog::sharedLog()->print(")");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~
		}
		else
		{
			// . ~~~~
			PLScopeBasedLog::sharedLog()->print(
					"Dummy connection. Returned empty tree");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~
		}

		_updatedIterators.erase(inIterator);
	}
	// ...else set updating status.
	else
	{
		theResult->root = PLReflectionTree::sharedGraph()->
				createNodeWithValue(NULL);
		theResult->branches = NULL;

		// If input character contains on set...
		if (_set->containsCharacter(inCharacter))
		{
			// . ~~~~
			PLScopeBasedLog::sharedLog()->print(
					"Symbol accepted. Reflector will finish on next symbol.");
			PLScopeBasedLog::sharedLog()->endLine();
			// . ~~~~

			theResult->updateStatus = PLCharacterReflectorUpdating;
			_updatedIterators[inIterator] = (NULL == _reflection) ? NULL :
					new PLReflection(_reflection,
							new PLCharacter(inCharacter));

			if (NULL == _reflection)
			{
				// . ~~~~
				PLScopeBasedLog::sharedLog()->print(
						"No reflection added - it's dummy");
				PLScopeBasedLog::sharedLog()->endLine();
				// . ~~~~
			}
			else
			{

				// . ~~~~
				PLScopeBasedLog::sharedLog()->print("Created reflection ");
				PLScopeBasedLog::sharedLog()->print(
						_updatedIterators[inIterator]);
				PLScopeBasedLog::sharedLog()->print(" with argument ");
				PLScopeBasedLog::sharedLog()->print(
						*((char *)_updatedIterators[inIterator]->
								getArgument()));
				PLScopeBasedLog::sharedLog()->endLine();
				// . ~~~~
			}
		}
	}

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	return theResult;
}

///////////////////////////////////////////////////////////////////////////////
PLString *PLCharacterReflector::description()
{
	PLString *theDescription = new PLString();

	theDescription->append("<Character set reflection ");
	theDescription->append(_set->description());
	theDescription->append(">");

	return theDescription;
}
