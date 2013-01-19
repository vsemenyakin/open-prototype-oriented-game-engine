/*
 * PLCharacterReflector_Syntax.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLCharacterReflector_Syntax.h"

#include "../Reflectors/PLCharacterReflector.h"
#include "../../Behavior/Reflection/PLReflection.h"
#include "../Reflectors/PLCharacterStreamReflector.h"

#include <fstream.h>

///////////////////////////////////////////////////////////////////////////////
// *** Functions for reflections
///////////////////////////////////////////////////////////////////////////////
void pushIdentifierCharacterProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->pushIdentifierCharacter(
			*((PLCharacter *)inArguments));

	std::cout << "Next identifier character: " <<
			*((PLCharacter *)inArguments) << std::endl;
}

void programIdentifierFinishedProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->programIdentifierFinished();

	std::cout << "Program identifier finished" << std::endl;
}

void constantIdentifierFinishedProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->constantIdentifierFinished();

	std::cout << "Constant identifier finished" << std::endl;
}

void pushComplexNumberCharacterLeftProxyFunction(void *inTarget,
		void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->pushComplexNumberCharacterLeft(
			*((PLCharacter *)inArguments));

	std::cout << "Next left complex number part character: " <<
			*((PLCharacter *)inArguments) << std::endl;
}

void setIsNumberComaBasedProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->setIsNumberComaBased();

	std::cout << "Number is coma-based" << std::endl;
}

void pushComplexNumberCharacterRightProxyFunction(void *inTarget,
		void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->pushComplexNumberCharacterRight(
			*((PLCharacter *)inArguments));

	std::cout << "Next right complex number part character: " <<
			*((PLCharacter *)inArguments) << std::endl;
}

void numberFinishedProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->numberFinished();

	std::cout << "Number finished" << std::endl;
}

void setFinishedOKStateProxyFunction(void *inTarget, void *inArguments)
{
	((PLCharacterReflector_Syntax *)inTarget)->setFinishedOKState();

	std::cout << "Machine finished correctly" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// *** Methods
///////////////////////////////////////////////////////////////////////////////
PLCharacterReflector_Syntax::PLCharacterReflector_Syntax()
{
}

PLCharacterReflector_Syntax::~PLCharacterReflector_Syntax()
{
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterStreamReflector *PLCharacterReflector_Syntax::reflector()
{
	// *****************************
	// Initialazing from constructor
	// *****************************

	//
	_parseTreeRoot = new parseTreeNode();

	parseTreeNonterminal *theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "program";
	theNonterminal->nextNode = NULL;

	_parseTreeRoot->nonterminals.push_back(theNonterminal);

	_nowBuildingNodeA = &(theNonterminal->nextNode);
	_nowBuildingNodeB = NULL;
	_nowBuildingNodeC = NULL;
	_nowBuildingNodeD = NULL;

	//	delete _parseTreeRoot;

	// *****************
	// Help initializing
	// *****************
	//.

	// Reflections
	PLReflection *thePushIdentifierCharacterReflection = new PLReflection(this,
			pushIdentifierCharacterProxyFunction);

	PLReflection *theProgramIdentifierFinishedReflection = new PLReflection(
			this, programIdentifierFinishedProxyFunction);

	PLReflection *theConstantIdentifierFinishedReflection = new PLReflection(
			this, constantIdentifierFinishedProxyFunction);

	PLReflection *thePushComplexNumberCharacterLeftReflection =
			new PLReflection(this,
					pushComplexNumberCharacterLeftProxyFunction);

	PLReflection *theSetIsNumberComaBasedReflection = new PLReflection(this,
			setIsNumberComaBasedProxyFunction);

	PLReflection *thePushComplexNumberCharacterRightReflection =
			new PLReflection(this,
					pushComplexNumberCharacterRightProxyFunction);

	PLReflection *theNumberFinishedReflection =
			new PLReflection(this, numberFinishedProxyFunction);

	PLReflection *theSetFinishedOKStateReflection = new PLReflection(this,
			setFinishedOKStateProxyFunction);

	// Help marks for machine building
	PLCharacterStreamReflectorMark *theMarkA = NULL;
	PLCharacterStreamReflectorMark *theMarkB = NULL;
	PLCharacterStreamReflectorMark *theMarkC = NULL;
	PLCharacterStreamReflectorMark *theMarkD = NULL;

	// For whitespace and comment
	PLCharacterStreamReflectorMark *theMarkE = NULL;
	PLCharacterStreamReflectorMark *theMarkF = NULL;

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

	// Whitespace
	PLCharacterSet *theWhitespace = new PLCharacterSet();
	theWhitespace->addCharacter(' ');
	theWhitespace->addCharacter('\t');
	theWhitespace->addCharacter('\n');

	// Symbols
	PLCharacterSet *theSymbols = new PLCharacterSet();
	theSymbols->addSet(theDigits);
	theSymbols->addSet(theLetters);
	theSymbols->addSet(theWhitespace);

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
	// identifier
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
	// identifier
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
	//    identifier
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
	_errors.push_back(PL_STR("syntax error"));

	//
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA,
			theWhitespace, PLReflection::dummyReflection());

	theMarkE = NULL;
	theProgrammReflection->makeBranchWithString(theMarkA, &theMarkE,
			PL_STR("(*"));

	theProgrammReflection->makeBranchWithSet(theMarkE, &theMarkE, theSymbols,
			PLReflection::dummyReflection());

	theProgrammReflection->makeBranchWithString(theMarkE, &theMarkA,
			 PL_STR("*)"));

	// identifier loops
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB, theLetters,
			thePushIdentifierCharacterReflection);


	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theLetters,
			thePushIdentifierCharacterReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theDigits,
			thePushIdentifierCharacterReflection);

	//
	theMarkC = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkC,
			this->setForSymbol(';'), theProgramIdentifierFinishedReflection);

	//
	theMarkD = NULL;
	theProgrammReflection->makeEmptyBranch(theMarkC, &theMarkD);

	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkD, &theMarkA,
			PL_STR("BEGIN"));

	theMarkB = NULL;
	theProgrammReflection->makeEmptyBranch(theMarkA, &theMarkB);

	//
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA,
			theWhitespace, PLReflection::dummyReflection());

	theMarkE = NULL;
	theProgrammReflection->makeBranchWithString(theMarkA, &theMarkE,
			PL_STR("(*"));

	theProgrammReflection->makeBranchWithSet(theMarkE, &theMarkE, theSymbols,
			PLReflection::dummyReflection());

	theProgrammReflection->makeBranchWithString(theMarkE, &theMarkA,
			 PL_STR("*)"));

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkB, &theMarkA,
			PL_STR("END"));

	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('.'), theSetFinishedOKStateReflection);

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithString(theMarkC, &theMarkA,
			PL_STR("CONST"));

	//
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA,
			theWhitespace, PLReflection::dummyReflection());

	theMarkE = NULL;
	theProgrammReflection->makeBranchWithString(theMarkA, &theMarkE,
			PL_STR("(*"));

	theProgrammReflection->makeBranchWithSet(theMarkE, &theMarkE, theSymbols,
			PLReflection::dummyReflection());

	theProgrammReflection->makeBranchWithString(theMarkE, &theMarkA,
			 PL_STR("*)"));

	//
	theProgrammReflection->makeBranchWithSet(theMarkC, &theMarkC,
			theWhitespace, PLReflection::dummyReflection());

	theMarkE = NULL;
	theProgrammReflection->makeBranchWithString(theMarkC, &theMarkE,
			PL_STR("(*"));

	theProgrammReflection->makeBranchWithSet(theMarkE, &theMarkE, theSymbols,
			PLReflection::dummyReflection());

	theProgrammReflection->makeBranchWithString(theMarkE, &theMarkC,
			 PL_STR("*)"));

	theProgrammReflection->makeEmptyBranch(theMarkA, &theMarkD);

	theMarkC = theMarkA;

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB, theLetters,
			thePushIdentifierCharacterReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theLetters,
			thePushIdentifierCharacterReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB, theDigits,
			thePushIdentifierCharacterReflection);

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA,
			this->setForSymbol('='), theConstantIdentifierFinishedReflection);

	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('\''), PLReflection::dummyReflection());

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA, theDigits,
			thePushComplexNumberCharacterLeftReflection);

	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA, theDigits,
			thePushComplexNumberCharacterLeftReflection);

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol(','), theSetIsNumberComaBasedReflection);

	theProgrammReflection->makeBranchWithString(theMarkA, &theMarkB,
			PL_STR("EXP"));

	//
	theMarkA = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkA, theDigits,
			thePushComplexNumberCharacterRightReflection);

	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkA, theDigits,
			thePushComplexNumberCharacterRightReflection);

	//
	theMarkB = NULL;
	theProgrammReflection->makeBranchWithSet(theMarkA, &theMarkB,
			this->setForSymbol('\''), theNumberFinishedReflection);

	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkC,
			this->setForSymbol(';'), PLReflection::dummyReflection());

	//
	theProgrammReflection->makeBranchWithSet(theMarkB, &theMarkB,
			theWhitespace, PLReflection::dummyReflection());

	theMarkE = NULL;
	theProgrammReflection->makeBranchWithString(theMarkB, &theMarkE,
			PL_STR("(*"));

	theProgrammReflection->makeBranchWithSet(theMarkE, &theMarkE, theSymbols,
			PLReflection::dummyReflection());

	theProgrammReflection->makeBranchWithString(theMarkE, &theMarkB,
			 PL_STR("*)"));

	return theProgrammReflection;
}

///////////////////////////////////////////////////////////////////////////////
// Identifier
void PLCharacterReflector_Syntax::pushIdentifierCharacter(
		PLCharacter inCharacter)
{
	_identifierRegister += inCharacter;
}

void PLCharacterReflector_Syntax::programIdentifierFinished()
{
	_programName = _identifierRegister;

	// lexic
	//.
	_lexemsLine.push_back(new lexem(PL_STR("PROGRAM"),
			lexem_class_program_word));

	_lexemsLine.push_back(new lexem(_identifierRegister,
			lexem_class_identefier));

	// syntax
	//.
	parseTreeNode *theNode = new parseTreeNode();

	// program-word
	parseTreeNonterminal *theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "program-word";
	theNonterminal->nextNode = NULL;
	theNode->nonterminals.push_back(theNonterminal);

	// identifier
	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "identifier";
	theNonterminal->nextNode = NULL;
	theNode->nonterminals.push_back(theNonterminal);

	// block
	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "block";
	theNonterminal->nextNode = NULL;
	theNode->nonterminals.push_back(theNonterminal);

	//.
	// declarations
	parseTreeNode *theBlockNode = new parseTreeNode();
	theNonterminal->nextNode = theBlockNode;

	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "declarations";
	theNonterminal->nextNode = NULL;
	theBlockNode->nonterminals.push_back(theNonterminal);

	_nowBuildingNodeC = &theNonterminal->nextNode;

	// begin
	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "begin-word";
	theNonterminal->nextNode = NULL;
	theBlockNode->nonterminals.push_back(theNonterminal);

	// statements list
	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "statements-list";
	theNonterminal->nextNode = NULL;
	theBlockNode->nonterminals.push_back(theNonterminal);

	// end
	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "end-word";
	theNonterminal->nextNode = NULL;
	theBlockNode->nonterminals.push_back(theNonterminal);


	// set next node
	*_nowBuildingNodeA = theNode;

	// set block pointer
	_nowBuildingNodeA = &theNonterminal->nextNode;


	_identifierRegister.clear();
}

void PLCharacterReflector_Syntax::constantIdentifierFinished()
{
	__lastIdentifier = _identifierRegister;

	// lexic
	//.
	_lexemsLine.push_back(new lexem(_identifierRegister,
			lexem_class_identefier));
	_lexemsLine.push_back(new lexem(PL_STR("="), lexem_class_equals_symbol));

	// syntax
	//.

	if (_nowBuildingNodeD == NULL)
	{
		parseTreeNode *theNodeA = new parseTreeNode();

		// const word
		parseTreeNonterminal *theNonterminal = new parseTreeNonterminal();
		theNonterminal->lexemName = "constant-word";
		theNonterminal->nextNode = NULL;
		theNodeA->nonterminals.push_back(theNonterminal);

		// constant declarations
		theNonterminal = new parseTreeNonterminal();
		theNonterminal->lexemName = "constant-declarations";
		theNonterminal->nextNode = NULL;
		theNodeA->nonterminals.push_back(theNonterminal);

		*_nowBuildingNodeC = theNodeA;
		_nowBuildingNodeD = &theNonterminal->nextNode;
	}

	// delcaration
	parseTreeNode *theNodeA = new parseTreeNode();

	// program-word
	// new declaration on _nowBuildingNodeD
	parseTreeNonterminal *theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "identifier-nonterminal";
	theNonterminal->nextNode = NULL;
	theNodeA->nonterminals.push_back(theNonterminal);

	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "equals-nonterminal";
	theNonterminal->nextNode = NULL;
	theNodeA->nonterminals.push_back(theNonterminal);

	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "constant-nonterminal";
	theNonterminal->nextNode = NULL;
	theNodeA->nonterminals.push_back(theNonterminal);
	_nowBuildingNodeC = &theNonterminal->nextNode;

	// declaration
	parseTreeNode *theNodeB = new parseTreeNode();

	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "constant-declaration-nonterminal";
	theNonterminal->nextNode = theNodeA;
	theNodeB->nonterminals.push_back(theNonterminal);

	theNonterminal = new parseTreeNonterminal();
	theNonterminal->lexemName = "constant-declarations-list-nonterminal";
	theNonterminal->nextNode = NULL;
	theNodeB->nonterminals.push_back(theNonterminal);

	*_nowBuildingNodeD = theNodeB;
	_nowBuildingNodeD = &theNonterminal->nextNode;

	_identifierRegister.clear();
}

// Number
void PLCharacterReflector_Syntax::pushComplexNumberCharacterLeft(
		PLCharacter inCharacter)
{
	_numberRegister.leftPart += inCharacter;
}

void PLCharacterReflector_Syntax::setIsNumberComaBased()
{
	_numberRegister.isComaFormat = true;
}

void PLCharacterReflector_Syntax::pushComplexNumberCharacterRight(
		PLCharacter inCharacter)
{
	_numberRegister.rightPart += inCharacter;
}

void PLCharacterReflector_Syntax::numberFinished()
{
	if (_constants.find(__lastIdentifier) != _constants.end())
	{
		PLString *theString = new PLString("Semantic error [");
		theString->append(&__lastIdentifier);
		theString->append("]: same constant's names exists");

		_errors.push_back(theString);
	}
	else
	{
		_constants[__lastIdentifier] = _numberRegister.getDouble();

		// lexic
		//.
		_lexemsLine.push_back(new lexem(PL_STR("\'"),
				lexem_class_quote));

		_lexemsLine.push_back(new lexem(_numberRegister.leftPart,
				lexem_class_constant_number_left_part));

		_lexemsLine.push_back(new lexem(PL_STR(
				_numberRegister.isComaFormat ? "," : "EXP"),
						lexem_class_constant_number_type_marker));

		_lexemsLine.push_back(new lexem(_numberRegister.leftPart,
				lexem_class_constant_number_right_part));

		_lexemsLine.push_back(new lexem(PL_STR("\'"),
				lexem_class_quote));

		// syntax
		//.
		parseTreeNode *theNode = new parseTreeNode();

		// program-word
		// constant on _nowBuildingNodeC
		parseTreeNonterminal *theNonterminal =
				new parseTreeNonterminal();
		theNonterminal->lexemName = "complex-number";
		theNonterminal->nextNode = NULL;
		theNode->nonterminals.push_back(theNonterminal);

		// set next node
		*_nowBuildingNodeC = theNode;
		_nowBuildingNodeC = NULL;
	}

	_numberRegister.reset();
	__lastIdentifier.clear();
}

// States
void PLCharacterReflector_Syntax::setFinishedOKState()
{
	_errors.pop_front();

	// lexic
	_lexemsLine.push_back(new lexem(PL_STR("BEGIN"),
			lexem_class_begin_word));
	_lexemsLine.push_back(new lexem(PL_STR(""), lexem_class_statements));
	_lexemsLine.push_back(new lexem(PL_STR("END"),
			lexem_class_end_word));
	_lexemsLine.push_back(new lexem(PL_STR("."),
			lexem_class_dot));

	std::cout << std::endl;
	std::cout << " -------- " << std::endl;
	std::cout << "Program name: " << _programName.getCString() << std::endl;
	std::cout << "Constants: " << std::endl;
	for (std::map<PLString, double>::iterator theIterator = _constants.begin();
			theIterator != _constants.end(); ++theIterator)
	{
		std::cout << theIterator->first.getCString() << " = " <<
				theIterator->second << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterReflector_Syntax::writeErrorsToFile(PLString &inFileName)
{
	if (_errors.size() != 0)
	{
		ofstream theStream(inFileName.getCString());

		for (std::list<PLString *>::iterator theIterator = _errors.begin();
				theIterator != _errors.end(); ++theIterator)
		{
			theStream << (*theIterator)->getCString() << std::endl;
		}
	}
}

void PLCharacterReflector_Syntax::writeLexemsToFile(PLString &inFileName)
{
	if (_errors.size() == 0)
	{
		ofstream theStream(inFileName.getCString());

		PLString *theLexemClassName = NULL;

		for (lexemsLine::iterator theIterator = _lexemsLine.begin();
				theIterator != _lexemsLine.end(); ++theIterator)
		{
			theLexemClassName = this->lexemClassNameForClass(
					(*theIterator)->lexemClass);
			theStream << theLexemClassName->getCString() << " : " <<
					(*theIterator)->symbols.getCString() << std::endl;
		}
	}
}

void PLCharacterReflector_Syntax::writeParseTreeToFile(PLString &inFileName)
{
	if (_errors.size() == 0)
	{
		ofstream theStream(inFileName.getCString());

		PLString *theDelta = new PLString();
		writeParseTreeToFileRecurse(theDelta, theStream, _parseTreeRoot);
	}
}

void PLCharacterReflector_Syntax::writeParseTreeToFileRecurse(
		PLString *inDelta, ostream &inStream, parseTreeNode *inRootNode)
{
	std::list<_parseTreeNonterminal *>::iterator theIterator =
			inRootNode->nonterminals.begin();

	for (; theIterator != inRootNode->nonterminals.end(); ++theIterator)
	{
		inStream << inDelta->getCString() <<
				(*theIterator)->lexemName.getCString() << std::endl;

		if ((*theIterator)->nextNode != NULL)
		{
			(*inDelta) += " ";

			writeParseTreeToFileRecurse(inDelta, inStream,
					(*theIterator)->nextNode);

			inDelta->erase(inDelta->length() - 1, 1);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void PLCharacterReflector_Syntax::writeAssemblerFile(PLString &inFileName)
{
	if (_errors.size() == 0)
	{
		ofstream theStream(inFileName.getCString());

		for (std::map<PLString, double>::iterator theIterator =
				_constants.begin(); theIterator != _constants.end();
						++theIterator)
		{
			theStream << theIterator->first.getCString() << " EQU " <<
					theIterator->second << std::endl;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
PLString *PLCharacterReflector_Syntax::lexemClassNameForClass(
		lexem_class inClass)
{
	if (_lexemClassNamesMap.size() == 0)
	{
		_lexemClassNamesMap[lexem_class_program_word] =
				PL_STR("lexem_class_program_word");
		_lexemClassNamesMap[lexem_class_identefier] =
				PL_STR("lexem_class_identefier");
		_lexemClassNamesMap[lexem_class_constant_word] =
				PL_STR("lexem_class_constant_word");
		_lexemClassNamesMap[lexem_class_equals_symbol] =
				PL_STR("lexem_class_equals_symbol");

		// Number
		_lexemClassNamesMap[lexem_class_quote] = PL_STR("lexem_class_quote");
		_lexemClassNamesMap[lexem_class_constant_number_left_part] =
				PL_STR("lexem_class_constant_number_left_part");
		_lexemClassNamesMap[lexem_class_constant_number_type_marker] =
				PL_STR("lexem_class_constant_number_type_marker");
		_lexemClassNamesMap[lexem_class_constant_number_right_part] =
				PL_STR("lexem_class_constant_number_right_part");

		// Program body
		_lexemClassNamesMap[lexem_class_begin_word] =
				PL_STR("lexem_class_begin_word");
		_lexemClassNamesMap[lexem_class_statements] =
				PL_STR("lexem_class_statements");
		_lexemClassNamesMap[lexem_class_end_word] =
				PL_STR("lexem_class_end_word");
		_lexemClassNamesMap[lexem_class_dot] =
				PL_STR("lexem_class_dot");

		// Comment
		_lexemClassNamesMap[lexem_class_comment_begin] =
				PL_STR("lexem_class_comment_begin");
		_lexemClassNamesMap[lexem_class_comment] =
				PL_STR("lexem_class_comment");
		_lexemClassNamesMap[lexem_class_comment_end] =
				PL_STR("lexem_class_comment_end");
	}

	return _lexemClassNamesMap[inClass];
}

///////////////////////////////////////////////////////////////////////////////
PLCharacterSet *PLCharacterReflector_Syntax::setForSymbol(
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
