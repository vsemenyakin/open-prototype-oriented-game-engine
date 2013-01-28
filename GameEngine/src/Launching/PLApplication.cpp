///////////////////////////////////////////////////////////////////////////////
#include "PLApplication.h"

#include <iostream>
#include <fstream>

#include <windows.h>

#include "../Base/PLCore.h"
#include "../OSDepended/Interface/PLGraphic.h"

#include "../CoreCollections/PL_core_graph.h"

#include "../Base/Memory/PLAutoPointer.h"

//#include "../OSDepended/Implementation/Windows/PLWindow_windows.h"

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
PLError *PLApplication::start()
{
	owning_ref<B> theOwningReference = owning_ref<B>::create();
	knowing_ref<A> theAssignedKnowingReference =
			cast_ref<A>(theOwningReference);

	owning_ref<A> theOwningReferenceNumerTwo = cast_ref<A>(theOwningReference);

	//std::cout << *theOwningReference << std::endl;
	//std::cout << *theAssignedKnowingReference << std::endl;

//	owning_ref<A> theA = cast_ref<A>(theB);


//	owning_ref<A> theAPointer = owning_ref<B>::create();

	/*
	PLWindow *theWindow = new PLWindow("First window",
			PLCreateRectangle(0.0, 0.0, 640.0, 480.0));

	theWindow->show();
	theWindow->setFocus();

	PLKeyboardEventHandler *theKeyboardEventsHandler =
			new PLKeyboardEventHandler();
	theWindow->getRunLoop()->assignHandler(theKeyboardEventsHandler);
	theKeyboardEventsHandler->addCallback(callback);

	theWindow->getRunLoop()->run();
	*/

	std::cout << "PLApplication finished" << std::endl;

	return 0;
}
