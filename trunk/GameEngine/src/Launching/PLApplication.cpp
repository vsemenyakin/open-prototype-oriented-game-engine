///////////////////////////////////////////////////////////////////////////////
#include "PLApplication.h"

#include <iostream>
#include <fstream>

#include <windows.h>

#include "../Base/PLCore.h"

#include "../View/PLGraphic.h"

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
void callback(void *inEventMessage)
{
	std::cout << "Key pressed" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
PLError *PLApplication::start()
{
	PLWindow *theWindow = new PLWindow("First window",
			PLCreateRectangle(100.0, 100.0, 500.0, 500.0));

	theWindow->setFocus();
	theWindow->show();

	PLKeyboardEventHandler *theKeyboardEventsHandler =
			new PLKeyboardEventHandler();
	theWindow->getRunLoop()->assignHandler(theKeyboardEventsHandler);

	theKeyboardEventsHandler->addCallback(callback);

	bool theExecutingFlag = true;

	MSG theMessage;
	while (theExecutingFlag)
	{
		if (PeekMessage(&theMessage, NULL, 0, 0, PM_REMOVE))
		{
			if (theMessage.message == WM_QUIT) // Have We Received A Quit Message?
			{
				theExecutingFlag = false; // If So done = TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&theMessage);				// Translate The Message
				DispatchMessage(&theMessage);				// Dispatch The Message
			}
		}
		else
		{
			//
		}
	}

	std::cout << "PLApplication finished." << std::endl;

	//while (true);

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
