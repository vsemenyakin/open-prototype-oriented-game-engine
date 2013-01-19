/*
 * PLStringReflector.cpp
 *
 *  Created on: Jan 2, 2013
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLStringReflector.h"

#include "../../Base/Diagnostic/PLScopeBasedLog.h"

///////////////////////////////////////////////////////////////////////////////
PLStringReflector::PLStringReflector(PLString *inString)
{
	_string.append(inString);
}

PLStringReflector::~PLStringReflector()
{
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterReflectorUpdatingResult *PLStringReflector::updateWithSymbol(
		PLCharacter inCharacter)
{
	return this->updateForRootIteratorWithSymbol(NULL, inCharacter);
}

PLCharacterReflectorUpdatingResult
		*PLStringReflector::updateForRootIteratorWithSymbol(
				PLReflectionTree::node_iterator *inIterator,
						PLCharacter inCharacter)
{
	// Get grow point
	PLGrowPoint *theGrowPoint = NULL;
	if (_updatedIndexes.find(inIterator) == _updatedIndexes.end())
	{
		theGrowPoint = new PLGrowPoint();

		theGrowPoint->index = 0;
		theGrowPoint->root = PLReflectionTree::sharedGraph()->
				createNodeWithValue(NULL);

		_updatedIndexes[inIterator] = theGrowPoint;
	}
	else
	{
		theGrowPoint = _updatedIndexes[inIterator];
	}

	// Create result
	PLCharacterReflectorUpdatingResult *theResult =
			new PLCharacterReflectorUpdatingResult();

	theResult->root =
			PLReflectionTree::sharedGraph()->createNodeWithValue(NULL);
	theResult->branches = NULL;

	// Set updating result
	if (theGrowPoint->index == _string.length())
	{
		PLReflectionTree::node_iterator *theIterator = theResult->root->
				createNextNodeWithValue(PLReflection::dummyReflection(), NULL);

		theResult->updateStatus = PLCharacterReflectorFinished;

		theResult->branches = new PLReflectionTreeIterationFront();
		theResult->branches->push_back(theIterator);

		_updatedIndexes.erase(inIterator);
	}
	else
	{
		if (_string[theGrowPoint->index] == inCharacter)
		{
			theResult->updateStatus = PLCharacterReflectorUpdating;
			++theGrowPoint->index;
		}
		else
		{
			theResult->updateStatus = PLCharacterReflectorFailed;

			_updatedIndexes.erase(inIterator);
		}
	}

	return theResult;
}

///////////////////////////////////////////////////////////////////////////////
PLString *PLStringReflector::description()
{
	PLString *theDescription = new PLString();

	theDescription->append("<String reflection ");
	theDescription->append(&_string);
	theDescription->append(">");

	return theDescription;
}
