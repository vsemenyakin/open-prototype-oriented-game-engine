/*
 * PLCharacterReflector_StressTests.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterReflector_StressTests.h"

#include "../Reflectors/PLCharacterReflector.h"
#include "../../Behavior/Reflection/PLReflection.h"
#include "../Reflectors/PLCharacterStreamReflector.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
void PLPushNumberToReflection(void *inTarget, void *inArguments)
{
	std::cout << *((char *)inArguments) << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterReflector_StressTests::PLCharacterReflector_StressTests()
{
	// Set as NULL cached sets

}

PLCharacterReflector_StressTests::~PLCharacterReflector_StressTests()
{
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLCharacterReflector_StressTests::reflector()
{
	// *****************
	// Help initializing
	// *****************
	//.
	PLReflection *thePushSymbolReflection = new PLReflection(NULL,
			PLPushNumberToReflection);

	PLCharacterStreamReflectorMark *theMarkA = NULL;
	PLCharacterStreamReflectorMark *theMarkB = NULL;
	PLCharacterStreamReflectorMark *theMarkC = NULL;
	PLCharacterStreamReflectorMark *theMarkD = NULL;

	// **************
	// Character sets
	// **************
	//.

	// Digits
	PLCharacterSet *theDigits = new PLCharacterSet();
	theDigits->addRange(PLChatacterRangeCreate('0', '9'));

	// Letters
	PLCharacterSet *theLetters = new PLCharacterSet();
	theLetters->addRange(PLChatacterRangeCreate('A', 'Z'));


	// *******************
	// "Signal" reflectors
	// *******************
	//.

	// -----------------------
	// Unsigned integer
	//
	//    0..9
	//   0 -> 0 _
	//         \_\ 0..9
	//

	// -----------------------
	// Complex number
	//
	// 0 -> 0 -> 0 -> 0
	//   |    ,    |
	//   |         .
	//   .       Unsigned integer
	// Unsigned integer
	//

	// -----------------------
	// Identifier
	//        _
	//  A..Z /_/ A..Z
	// 0 -> 0 _
	//       \_\ 0..9
	//

	// -----------------------
	// Constant
	//
	// 0 -> 0 -> 0 -> 0
	//   '    |     '
	//        .
	//  Complex number
	//

	// -----------------------
	// Constant declaration
	//
	// 0 -> 0 -> 0 -> 0 -> 0
	//   |    =    |    ;
	//   |         .
	//   .     Constant
	// Identifier
	//

	// -----------------------
	// Constant declarations
	//
	// 0 -> 0 _
	//   |   \_\ Constant declaration
	//   .
	// {CONST}
	//

	// -----------------------
	// Declarations
	//
	//  <0>
	// 0 -> 0
	//  \_/
	//   .
	//   |
	// Constant declarations
	//

	// -----------------------
	// Statements list
	//
	// 0 -> 0
	//  <0>
	//

	// -----------------------
	// Block
	//
	//     {BEGIN}    {END}
	//        |         |
	//        .         .
	// 0 -> 0 -> 0 -> 0 -> 0
	//   .         .
	//   |         |
	//   |    Statements list
	// Declarations
	//

	// -----------------------
	// Program
	//
	//    Identifier
	//        |
	//        .    ;         .
	// 0 -> 0 -> 0 -> 0 -> 0 -> 0
	//   .              .
	//   |              |
	// {PROGRAM}      Block

	PLCharacterStreamReflector *theProgrammReflection =
			new PLCharacterStreamReflector();

	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(
			theProgrammReflection->initialStateMark(), &theMarkA,
					PL_STR("PROGRAM"));

	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB, theLetters,
			thePushSymbolReflection);

	// Identifier loops
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theLetters,
			thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theDigits,
			thePushSymbolReflection);

	//
	theMarkC = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkC,
			this->setForSymbol(';'), thePushSymbolReflection);

	//
	theMarkD = NULL;
	theProgrammReflection->makeEmptyBranch(theMarkC, &theMarkD);

	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkD, &theMarkA,
			PL_STR("BEGIN"));

	theMarkB = NULL;
	theProgrammReflection->makeEmptyBranch(theMarkA, &theMarkB);

	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkB, &theMarkA,
			PL_STR("END"));

	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('.'), thePushSymbolReflection);

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkC, &theMarkA,
			PL_STR("CONST"));

	theProgrammReflection->makeEmptyBranch(theMarkA, &theMarkD);

	theMarkC = theMarkA;

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB, theLetters,
			thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theLetters,
			thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theDigits,
			thePushSymbolReflection);

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA,
			this->setForSymbol('='), thePushSymbolReflection);

	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('\''), thePushSymbolReflection);

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA, theDigits,
			thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA, theDigits,
			thePushSymbolReflection);

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol(','), thePushSymbolReflection);

	theProgrammReflection->makeBranchWithString(theMarkA, &theMarkB,
			PL_STR("EXP"));

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA, theDigits,
			thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA, theDigits,
			thePushSymbolReflection);

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('\''), thePushSymbolReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkC,
			this->setForSymbol(';'), thePushSymbolReflection);
/*
*/
	// ************************
	// "Stress test" reflectors
	// ************************

	// Machine #1
	//	 A   <0>   C
	// 0 -> 0 -> 0 -> 0
	//		 \_/
	//        B
	//
	PLCharacterStreamReflector *theReflectionA =
			new PLCharacterStreamReflector();

	theMarkA = NULL;
	theReflectionA->makeBranchWithSet(theReflectionA->initialStateMark(),
			&theMarkA, this->setForSymbol('A'), thePushSymbolReflection);

	theMarkB = NULL;
	theReflectionA->makeEmptyBranch(theMarkA, &theMarkB);
	theReflectionA->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('B'), thePushSymbolReflection);

	theMarkA = NULL;
	theReflectionA->makeBranchWithSet(theMarkB, &theMarkA,
				this->setForSymbol('C'), thePushSymbolReflection);


	// Machine #2
	//
	// 0 _
	// \__\ D
	theMarkA = NULL;
	theMarkB = NULL;

	PLCharacterStreamReflector *theReflectionB =
			new PLCharacterStreamReflector();

	theMarkA = theReflectionB->initialStateMark();
	theReflectionB->makeBranchWithSet(theReflectionB->initialStateMark(),
			&theMarkA, this->setForSymbol('D'), thePushSymbolReflection);


	// Main machine
	//
	//   #1   #2  {AB}
	// 0 -> 0 -> 0 -> 0
	theMarkA = NULL;
	theMarkB = NULL;

	PLCharacterStreamReflector *theMainMachine =
				new PLCharacterStreamReflector();

	theMainMachine->makeBranchWithSubreflection(
			theMainMachine->initialStateMark(), &theMarkA, theReflectionA,
					thePushSymbolReflection);

	theMainMachine->makeBranchWithSubreflection(theMarkA, &theMarkB,
			theReflectionB, thePushSymbolReflection);

	theMarkA = NULL;
	theMainMachine->makeBranchWithString(theMarkB, &theMarkA, PL_STR("YZ"));

	// Main machine
	//
	//   Z    A    B    C
	// 0 -> 0 -> 0 -> 0 -> 0
	//        \_ 0 -> 0 -> 0
	//         A   B    D
	//
	PLCharacterStreamReflector *theTestMachine =
				new PLCharacterStreamReflector();

	theMarkC = NULL;
	theTestMachine->makeBranchWithSet(theTestMachine->initialStateMark(),
			&theMarkC, this->setForSymbol('Z'), thePushSymbolReflection);

	//
	theMarkB = NULL;
	theTestMachine->makeBranchWithSet(theMarkC, &theMarkB,
			this->setForSymbol('A'), thePushSymbolReflection);

	theMarkA = NULL;
	theTestMachine->makeBranchWithSet(theMarkB, &theMarkA,
			this->setForSymbol('B'), thePushSymbolReflection);

	theMarkB = NULL;
	theTestMachine->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('C'), thePushSymbolReflection);

	//
	theMarkB = NULL;
	theTestMachine->makeBranchWithSet(theMarkC, &theMarkB,
			this->setForSymbol('A'), thePushSymbolReflection);

	theMarkA = NULL;
	theTestMachine->makeBranchWithSet(theMarkB, &theMarkA,
			this->setForSymbol('B'), thePushSymbolReflection);

	theMarkB = NULL;
	theTestMachine->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('D'), thePushSymbolReflection);

	//return theTestMachine;
	return theProgrammReflection;
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterSet *PLCharacterReflector_StressTests::setForSymbol(
		PLCharacter inSymbol)
{
	PLCharacterSet *theSet = NULL;

	if (_sets.find(inSymbol) == _sets.end())
	{
		theSet = new PLCharacterSet();
		theSet->addCharacter(inSymbol);

		_sets[inSymbol] = theSet;
	}
	else
	{
		theSet = _sets[inSymbol];
	}

	return theSet;
}

PLCharacterSet *PLCharacterReflector_StressTests::setForRange(
		PLCharacter inBeginSymbol, PLCharacter inEndSymbol,
				std::string &inName)
{
	PLCharacterSet *theSet = NULL;

	if (_rangeSets.find(inName) == _rangeSets.end())
	{
		theSet = new PLCharacterSet();
		theSet->addRange(PLChatacterRangeCreate(inBeginSymbol, inEndSymbol));

		_rangeSets[inName] = theSet;
	}
	else
	{
		theSet = _rangeSets[inName];
	}

	return theSet;
}

