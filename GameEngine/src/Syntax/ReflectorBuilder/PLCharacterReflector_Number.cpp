/*
 * PLCharacterReflector_Number.cpp
 *
 *  Created on: Nov 23, 2012
 *      Author: Admin
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterReflector_Number.h"

#include "../Reflectors/PLCharacterReflector.h"
#include "../Reflectors/PLCharacterStreamReflector.h"

#include "../PLCharacterSet.h"

#include "../../Behavior/Reflection/PLReflection.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
void PLPushNumberToReflection_(void *inTarget, void *inArguments)
{
	std::cout << *((char *)inArguments) << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterReflector_Number::PLCharacterReflector_Number()
{
	// Set as NULL cached sets
	_set_0_9 = NULL;
	_set_0 = NULL;
	_set_1_9 = NULL;
	_set_DOT = NULL;
}

PLCharacterReflector_Number::~PLCharacterReflector_Number()
{
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLCharacterReflector_Number::reflector()
{
	// Push symbol reflection
	PLReflection *thePushSymbolReflection = new PLReflection(NULL,
			PLPushNumberToReflection_);

	// *******************
	// Real part reflector
	// *******************
	PLCharacterStreamReflector *theIntegerPartReflector =
			new PLCharacterStreamReflector();

	// Marker registers
	PLCharacterStreamReflectorMark *theMarkA = NULL;

	// Zero branch
	theIntegerPartReflector->makeBranchWithSet(
			theIntegerPartReflector->initialStateMark(), &theMarkA, set_0(),
					thePushSymbolReflection);

	// Number branch
	theMarkA = NULL;
	theIntegerPartReflector->makeBranchWithSet(
			theIntegerPartReflector->initialStateMark(), &theMarkA, set_1_9(),
					thePushSymbolReflection);

	theIntegerPartReflector->makeBranchWithSet(theMarkA, &theMarkA, set_0_9(),
					thePushSymbolReflection);

	// ***********************
	// Friction part reflector
	// ***********************
	PLCharacterStreamReflector *theFractionalPartReflector =
			new PLCharacterStreamReflector();

	// Zero loop
	theMarkA = theFractionalPartReflector->initialStateMark();
	theFractionalPartReflector->makeBranchWithSet(
			theFractionalPartReflector->initialStateMark(), &theMarkA, set_0(),
			thePushSymbolReflection);

	// Number state
	theMarkA = NULL;
	theFractionalPartReflector->makeBranchWithSet(
			theFractionalPartReflector->initialStateMark(), &theMarkA,
					set_1_9(), thePushSymbolReflection);

	theFractionalPartReflector->makeBranchWithSet(theMarkA, &theMarkA,
			set_1_9(), thePushSymbolReflection);


	// Zero connection
	PLCharacterStreamReflectorMark *theMarkB =
			theFractionalPartReflector->initialStateMark();
	theFractionalPartReflector->makeBranchWithSet(theMarkA, &theMarkB, set_0(),
			thePushSymbolReflection);

	// ****************
	// Number reflector
	//*****************
	PLCharacterStreamReflector *theNumberReflector =
				new PLCharacterStreamReflector();

	theMarkA = NULL;
	theNumberReflector->makeBranchWithSubreflection(
			theNumberReflector->initialStateMark(), &theMarkA,
					theIntegerPartReflector, thePushSymbolReflection);

	theMarkB = NULL;
	theNumberReflector->makeBranchWithSet(theMarkA, &theMarkB, set_DOT(),
			thePushSymbolReflection);

	theMarkA = NULL;
	theNumberReflector->makeBranchWithSubreflection(theMarkB, &theMarkA,
			theFractionalPartReflector, thePushSymbolReflection);

	return theNumberReflector;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterSet *PLCharacterReflector_Number::set_0_9()
{
	if (NULL == _set_0_9)
	{
		_set_0_9 = new PLCharacterSet();
		_set_0_9->addRange(PLChatacterRangeCreate('0', '9'));
	}

	return _set_0_9;
}

PLCharacterSet *PLCharacterReflector_Number::set_0()
{
	if (NULL == _set_0)
	{
		_set_0 = new PLCharacterSet();
		_set_0->addCharacter('0');
	}

	return _set_0;
}

PLCharacterSet *PLCharacterReflector_Number::set_1_9()
{
	if (NULL == _set_1_9)
	{
		_set_1_9 = new PLCharacterSet();
		_set_1_9->addRange(PLChatacterRangeCreate('1', '9'));
	}

	return _set_1_9;
}

PLCharacterSet *PLCharacterReflector_Number::set_DOT()
{
	if (NULL == _set_DOT)
	{
		_set_DOT = new PLCharacterSet();
		_set_DOT->addCharacter('.');
	}

	return _set_DOT;
}
