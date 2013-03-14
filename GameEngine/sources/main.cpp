
//#include "Launching/PLUnitTesting.h"

#include <iostream>
#include <application/implementation/PLApplication/PLApplication_windows.h>

// my test comment
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//#define UNIT_TESTING
#define APPLICATION_EXECUTION

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
	PLApplication_windows theApplication;
	theApplication.init();
	theApplication.start();
#endif

	// TODO return here PLError
	return 0;
}
