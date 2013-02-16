///////////////////////////////////////////////////////////////////////////////
#include "PLApplication.h"
#include "PLUnitTesting.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//#define UNIT_TESTING
//#define APPLICATION_EXECUTION

///////////////////////////////////////////////////////////////////////////////
int main()
{

// Unit testing
#ifdef UNIT_TESTING
	PLUnitTesting theUnitTesting;
	theUnitTesting.perform();
#endif

// Application execution
#ifdef APPLICATION_EXECUTION
	PLApplication theApplication;
	theApplication.start();
#endif

	// TODO return here PLError
	return 0;
}
