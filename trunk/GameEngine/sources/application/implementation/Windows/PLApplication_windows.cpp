///////////////////////////////////////////////////////////////////////////////
#include "PLApplication_windows.h"

#include <windows.h>

// Utilities
#include <iostream>
#include <fstream>

// Framework core
#include "PLGraphic_windows.h"

#include "Multithreading/PLThread_windows.h"
#include "EventHandling/PLRunLoop_windows.h"

///////////////////////////////////////////////////////////////////////////////
void testCallback(void *inTarget, void *inArgument)
{
	PLCharacter theSymbol = *((PLCharacter *)inArgument);
	std::cout << theSymbol << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
PLString *plStringFromFile(PLString &inFileName)
{
	PLString *theString = new PLString();

	std::fstream theStream(inFileName.getCString());

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

// TODO put here PLLog
///////////////////////////////////////////////////////////////////////////////
PLApplication_windows::PLApplication_windows()
{
}

PLApplication_windows::~PLApplication_windows()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLApplication_windows::init()
{
	// Create main thread object
	PLThread_windows::createMainThreadObject(GetCurrentThread());

	// Create main window object
	PLWindow_windows *theWindow = new PLWindow_windows((char *)"First window",
			PLCreateRectangle(0.0, 0.0, 640.0, 480.0));

	theWindow->show();
	theWindow->setFocus();

	/*
		PLKeyboardEventHandler *theKeyboardEventsHandler =
				new PLKeyboardEventHandler();
		theWindow->getRunLoop()->assignHandler(theKeyboardEventsHandler);
		theKeyboardEventsHandler->addCallback(callback);
	*/
	theWindow->getRunLoop()->run();
}

///////////////////////////////////////////////////////////////////////////////
PLError *PLApplication_windows::start()
{

//	owning_ref<B> theOwningReference = owning_ref<B>::create();
//	knowing_ref<A> theAssignedKnowingReference =
//			cast_ref<A>(theOwningReference);
//
//	owning_ref<A> theOwningReferenceNumerTwo = cast_ref<A>(theOwningReference);

	//
	//  _________
	// |     6   |
	// |  1    3 |  4    5
	// * -> * -> * -> * -> *
	// 1 <- 2    3    4    5
	//   2
//	testGraph::node_iterator theRootIterator =
//			testGraph::sharedGraph()->createNodeWithValue(1);
//
//	testGraph::node_iterator theHelpNodeIterator =
//			theRootIterator.createNextNodeWithValue(2, 1);
//
//	theHelpNodeIterator.connectToNode(theRootIterator, 2);
//
//	theHelpNodeIterator = theHelpNodeIterator.createNextNodeWithValue(3, 3);
//	theHelpNodeIterator.connectToNode(theRootIterator, 6);
//
//	theHelpNodeIterator = theHelpNodeIterator.createNextNodeWithValue(4, 4);
//	theHelpNodeIterator = theHelpNodeIterator.createNextNodeWithValue(5, 5);
//
//	theRootIterator.graph()->writeToFile("graph.txt");

	//std::cout << *theOwningReference << std::endl;
	//std::cout << *theAssignedKnowingReference << std::endl;

//	owning_ref<A> theA = cast_ref<A>(theB);


//	owning_ref<A> theAPointer = owning_ref<B>::create();

	std::cout << "PLApplication finished" << std::endl;

	return 0;
}
