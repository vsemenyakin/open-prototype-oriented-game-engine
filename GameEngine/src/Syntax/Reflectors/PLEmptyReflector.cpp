/*
 * PLEmptyReflector.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLEmptyReflector.h"

#include "../PLCharacterSet.h"
#include "../../Base/Diagnostic/PLScopeBasedLog.h"
#include "PLCharacterReflector.h"

///////////////////////////////////////////////////////////////////////////////
PLEmptyReflector::PLEmptyReflector()
{
	_wrappedReflector = new PLCharacterReflector(
			PLCharacterSet::anySymbolSet(), NULL);
}

PLEmptyReflector::~PLEmptyReflector()
{
}

///////////////////////////////////////////////////////////////////////////////
// *** Updating [IMPLEMENTATION: IPLCharacterReflector]
///////////////////////////////////////////////////////////////////////////////
PLCharacterReflectorUpdatingResult *PLEmptyReflector::updateWithSymbol(
		PLCharacter inCharacter)
{
	return updateForRootIteratorWithSymbol(NULL, inCharacter);
}

PLCharacterReflectorUpdatingResult *PLEmptyReflector::
		updateForRootIteratorWithSymbol(
				PLReflectionTree::node_iterator *inIterator,
						PLCharacter inCharacter)
{
	// . ~~~~
	PLScopeBasedLog::sharedLog()->print(
			"Updating <EMPTY> connection with character \'");
	PLScopeBasedLog::sharedLog()->print(inCharacter);
	PLScopeBasedLog::sharedLog()->print("\'");

	PLScopeBasedLog::sharedLog()->endLine();

	PLScopeBasedLog::sharedLog()->beingScope();
	// . ~~~~

	//PLCharacterReflectorUpdatingResult *theResult = _wrappedReflector->
	//		updateForRootIteratorWithSymbol(inIterator, inCharacter);

	PLCharacterReflectorUpdatingResult *theResult =
			new PLCharacterReflectorUpdatingResult();
	theResult->root = PLReflectionTree::sharedGraph()->
			createNodeWithValue(PLReflection::dummyReflection());
	theResult->updateStatus = PLCharacterReflectorFinished;

	//theResult->branches = NULL;

	PLReflectionTree::node_iterator *theIterator = theResult->root->
			createNextNodeWithValue(PLReflection::dummyReflection(), NULL);
	theResult->branches = new PLReflectionTreeIterationFront();
	theResult->branches->push_back(theIterator);

	// . ~~~~
	PLScopeBasedLog::sharedLog()->endScope();
	// . ~~~~

	return theResult;
}

///////////////////////////////////////////////////////////////////////////////
// *** Base behavior [IMPLEMENTATION: PLObject]
///////////////////////////////////////////////////////////////////////////////
PLString *PLEmptyReflector::description()
{
	return new PLString("<EMPTY>\0");
}
