///////////////////////////////////////////////////////////////////////////////
#include "PLApplication.h"

#include <iostream>
#include <fstream>

#include <windows.h>

#include "../Base/PLCore.h"
#include "../OSDepended/Interface/PLGraphic.h"

#include "../CoreCollections/PL_core_graph.h"

#include "../Base/Memory/PLAutoPointer.h"

#include "../OSDepended/Implementation/Windows/PLWindow_windows.h"

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
class A
{
public:
	virtual void foo()
	{
		std::cout << "First foo" << std::endl;
	}

	virtual ~A()
	{
		std::cout << ">>> Removed" << std::endl;
	}
};

class B : public A
{
public:
	virtual void foo()
	{
		std::cout << "First foo" << std::endl;
	}

	virtual ~B()
	{
	}
};

///////////////////////////////////////////////////////////////////////////////
typedef PL_core_graph<int, int> testGraph;

///////////////////////////////////////////////////////////////////////////////
PLError *PLApplication::start()
{
	PLWindow *theWindow = new PLWindow("First window",
			PLCreateRectangle(0.0, 0.0, 640.0, 480.0));

	theWindow->show();
	theWindow->setFocus();

	PLKeyboardEventHandler *theKeyboardEventsHandler =
			new PLKeyboardEventHandler();
	theWindow->getRunLoop()->assignHandler(theKeyboardEventsHandler);
	theKeyboardEventsHandler->addCallback(callback);

	theWindow->getRunLoop()->run();

//	owning_ref<B> theOwningReference = owning_ref<B>::create();
//	knowing_ref<A> theAssignedKnowingReference =
//			cast_ref<A>(theOwningReference);
//
//	owning_ref<A> theOwningReferenceNumerTwo = cast_ref<A>(theOwningReference);

	//
	//  _________
	// /     6   \
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
