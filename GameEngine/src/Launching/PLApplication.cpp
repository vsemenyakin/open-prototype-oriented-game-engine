///////////////////////////////////////////////////////////////////////////////
#include "PLApplication.h"

#include <iostream>
#include <fstream>

#include "../Syntax/ReflectorBuilder/PLCharacterReflector_Syntax.h"
//#include "../Syntax/ReflectorBuilder/PLCharacterReflector_Number.h"
#include "../Syntax/ReflectorBuilder/PLCharacterReflector_StressTests.h"

#include "../Syntax/Reflectors/PLCharacterStreamReflector.h"

#include "../Syntax/PLCharacterSet.h"
#include "../CoreCollections/PL_core_graph.h"

#include "../Base/PLCore.h"

#include "../Base/Diagnostic/PLLog.h"

#include "../View/PLWindow.h"

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void testCallback(void *inTarget, void *inArgument)
{
	PLCharacter theSymbol = *((PLCharacter *)inArgument);
	std::cout << theSymbol << std::endl;
}

// TODO put here PLLog
///////////////////////////////////////////////////////////////////////////////
PLApplication::PLApplication()
{
}

PLApplication::~PLApplication()
{
}

///////////////////////////////////////////////////////////////////////////////
PLString *plStringFromFile(PLString &inFileName)
{
	PLString *theString = new PLString();

	fstream theStream(inFileName.getCString());

	char theCharacter;

	while (false == theStream.eof())
	{
		theStream >> theCharacter;
		(*theString) += theCharacter;
	}

	return theString;
}

///////////////////////////////////////////////////////////////////////////////
PLError *PLApplication::start()
{
	PLWindow *theWindow = new PLWindow("First window",
			PLCreateRectangle(100.0, 100.0, 500.0, 500.0));

	theWindow->show();

	/*
	PLString *theString = plStringFromFile(*PL_STR("program.txt"));
	std::cout << theString->getCString() << std::endl;

	PLCharacterReflector_Syntax *theSyntaxReflector =
			new PLCharacterReflector_Syntax();

	//PLCharacterReflector_Number *theNumberReflector =
	//		new PLCharacterReflector_Number();

	//PLCharacter *theNumber = charactersFromCharBuffer("123.1010", 8);//"123.1010\0";
	//PLCharacter *theStressTest = charactersFromCharBuffer("ACYZ", 4);

	//PLCharacter *theStressTest = charactersFromCharBuffer("ZABD", 4);

	PLCharacter *theStressTest = charactersFromCharBuffer(theString->getCString(), theString->length());
	//PLCharacter *theStressTest = charactersFromCharBuffer("PROGRAMQWERTY;CONSTFIRSTCONST=\'00,00\'SECONDCONST=\'11,11\'BEGINEND.", 65);


	PLCharacterStreamReflector *theReflector =
			theSyntaxReflector->reflector();
//	PLCharacterStreamReflector *theReflector =
//			theNumberReflector->reflector();

	int i = 0;
	PLCharacterReflectorUpdatingResult *theResult = NULL;

	do
	{
		theResult = theReflector->updateWithSymbol(theStressTest[i++]);
		//theResult = theReflector->updateWithSymbol(theNumber[i++]);
	} while (theResult->updateStatus == PLCharacterReflectorUpdating);

	delete theReflector;

	std::cout << std::endl << "--------- " << std::endl;

	if (theResult->updateStatus == PLCharacterReflectorFinished &&
			theResult->root->edgesOut()->size() != 0)
	{
		i = 0;

		PLReflectionTree::node_iterator *theIterator =
				new PLReflectionTree::node_iterator(theResult->root);

		while (theIterator->edgesOut()->size() != 0 && i < 100)
		{
			std::cout << theIterator->_node << " : " << **theIterator
					<< " = " << theIterator->edgesOut()->size() << std::endl;

			(**theIterator)->call();

			theIterator->moveToNextNode(theIterator->edgesOut()->begin());
		}

		std::cout << theIterator->_node << " : " <<  **theIterator
				<< " = " << theIterator->edgesOut()->size() << std::endl;
		(**theIterator)->call();
	}
	else
	{
		std::cout << "Reflector failed" << std::endl;
	}

	theSyntaxReflector->writeErrorsToFile(*PL_STR("errors.txt"));
	theSyntaxReflector->writeLexemsToFile(*PL_STR("lixems.txt"));
	theSyntaxReflector->writeParseTreeToFile(*PL_STR("parseTree.txt"));
	theSyntaxReflector->writeAssemblerFile(*PL_STR("assemblerCode.txt"));

	std::cout << "PLApplication launched..." << std::endl;
	 */

	std::cout << "PLApplication launched..." << std::endl;

	while (true);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//void testNumber()
//{
//	PLCharacterReflector_Number *theNumberReflector =
//			new PLCharacterReflector_Number();
//
//	//char *theNumber = "123.4560\0";//"123.1010\0";
//	char *theNumber = "1.00000\0";
//
//	PLCharacterStreamReflector *theReflector = theNumberReflector->reflector();
//
//	int i = 0;
//	PLCharacterReflectorUpdatingResult *theResult = NULL;
//
//	do
//	{
//		theResult = theReflector->updateWithSymbol(theNumber[i++]);
//	} while (theResult->updateStatus == PLCharacterReflectorUpdating);
//
//	std::cout << std::endl << "--------- " << std::endl;
//
//	if (theResult->root->edgesOut()->size() != 0)
//	{
//		i = 0;
//
//		PLReflectionTree::node_iterator *theIterator =
//				new PLReflectionTree::node_iterator(theResult->root);
//
//		theIterator->moveToNextNode(theIterator->edgesOut()->begin());
//
//		while (theIterator->edgesOut()->size() != 0 && i < 100)
//		{
//			std::cout << **theIterator << std::endl;
//
//			(**theIterator)->call();
//
//			theIterator->moveToNextNode(theIterator->edgesOut()->begin());
//		}
//
//		std::cout << **theIterator << std::endl;
//		(**theIterator)->call();
//	}
//	else
//	{
//		std::cout << "Reflector failed" << std::endl;
//	}
//}
