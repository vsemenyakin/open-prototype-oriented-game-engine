/*
 * PLCharacterReflector_Syntax.h
 *
 *  Created on: Jan 3, 2013
 *      Author: Admin
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef PLCHARACTERREFLECTOR_SYNTAX_H_
#define PLCHARACTERREFLECTOR_SYNTAX_H_

///////////////////////////////////////////////////////////////////////////////
#include <map>
#include <list>

#include <math.h>

#include "../../Base/PLCore.h"

#include "../../CoreCollections/PL_core_graph.h"

#include "../PLCharacterSet.h"

///////////////////////////////////////////////////////////////////////////////
class PLCharacterStreamReflector;

///////////////////////////////////////////////////////////////////////////////
class PLCharacterReflector_Syntax
{
private:

	// *****
	// Types
	// *****

	// -------------
	// Lexic
	//.

	enum
	{
		lexem_class_program_word,
		lexem_class_identefier,
		lexem_class_constant_word,
		lexem_class_equals_symbol,

		// Number
		lexem_class_quote,
		lexem_class_constant_number_left_part,
		lexem_class_constant_number_type_marker,
		lexem_class_constant_number_right_part,

		// Program body
		lexem_class_begin_word,
		lexem_class_statements,
		lexem_class_end_word,
		lexem_class_dot,

		// Comment
		lexem_class_comment_begin,
		lexem_class_comment,
		lexem_class_comment_end
	} typedef lexem_class;

	std::map<lexem_class, PLString *> _lexemClassNamesMap;
	PLString *lexemClassNameForClass(lexem_class inClass);

	// Lexem data
	struct lexem_
	{
		lexem_(PLString inSymbols, lexem_class inLexemClass)
		{
			symbols = inSymbols;
			lexemClass = inLexemClass;
		}

		PLString symbols;
		lexem_class lexemClass;
	} typedef lexem;

	// Line
	typedef std::list<lexem *> lexemsLine;

	// --------------
	// Syntax
	//.

	// Tree
	struct _parseTreeNonterminal;

	struct
	{
		std::list<_parseTreeNonterminal *> nonterminals;
	} typedef parseTreeNode;

	struct _parseTreeNonterminal
	{
		PLString lexemName;
		parseTreeNode *nextNode;
	} typedef parseTreeNonterminal;

	//                       ...
	//                      __|__
	// [ parseTreeNonterminal   parseTreeNonterminal ]  ->  parseTreeNode
	//       nextRoot
	//         /|\

	// Number data
	struct _numberRegister
	{
		_numberRegister()
			: leftPart(), rightPart(), isComaFormat(false)
		{
		}

		double getDouble()
		{
			double theDouble = 0.0;

			// If only left part is exists
			if (rightPart.length() == 0)
			{
				return atof(leftPart.getCString());
			}

			// If left and right parts are exists
			if (isComaFormat)
			{
				// Coma form of the number
				PLString theString = leftPart + "." + rightPart;

				theDouble = atof(theString.getCString());
			}
			else
			{
				// Expanent form of the number
				theDouble = atoi(leftPart.getCString()) *
						exp(atof(rightPart.getCString()));
			}

			return theDouble;
		}

		void reset()
		{
			leftPart.clear();
			rightPart.clear();
			isComaFormat = false;
		}

		PLString leftPart;
		PLString rightPart;
		bool isComaFormat;
	} typedef numberRegister;

	// ------
	// Result
	//.

	// Registers
	PLString _identifierRegister;
	PLString __lastIdentifier;

	numberRegister _numberRegister;

	// Constants
	PLString _programName;
	std::map<PLString, double> _constants;

	// Unused elements (for lab work only)
	lexemsLine _lexemsLine;
	parseTreeNode *_parseTreeRoot;

	parseTreeNode **_nowBuildingNodeA;
	parseTreeNode **_nowBuildingNodeB;
	parseTreeNode **_nowBuildingNodeC;
	parseTreeNode **_nowBuildingNodeD;

	// ------------
	// Help methods
	//.
	PLCharacterSet *setForSymbol(PLCharacter inSymbol);

	// Help variables
	std::map<PLCharacter, PLCharacterSet *> _sets;
	std::list<PLString *> _errors;

public:
	//
	PLCharacterReflector_Syntax();
	virtual ~PLCharacterReflector_Syntax();

	//
	void processString(PLString *inString);

	// TODO: To do something with it (this methods should be private)
	// Identifier
	void pushIdentifierCharacter(PLCharacter inCharacter);

	void programIdentifierFinished();
	void constantIdentifierFinished();

	// Number
	void pushComplexNumberCharacterLeft(PLCharacter inCharacter);
	void setIsNumberComaBased();
	void pushComplexNumberCharacterRight(PLCharacter inCharacter);
	void numberFinished();

	// States
	void setFinishedOKState();

	// Reflector
	PLCharacterStreamReflector *reflector();

	// Output
	void writeErrorsToFile(PLString &inFileName);
	void writeLexemsToFile(PLString &inFileName);
	void writeParseTreeToFile(PLString &inFileName);
	void writeParseTreeToFileRecurse(PLString *inDelta, ostream &inStream,
			parseTreeNode *inRootNode);
	void writeAssemblerFile(PLString &inFileName);
};

#endif /* PLCHARACTERREFLECTOR_SYNTAX_H_ */
