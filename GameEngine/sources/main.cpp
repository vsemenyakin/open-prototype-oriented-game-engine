///////////////////////////////////////////////////////////////////////////////
//#define UNIT_TESTING
//#define APPLICATION_EXECUTION

///////////////////////////////////////////////////////////////////////////////

#include <iostream>

// =====================
// Unit testing includes
#ifdef UNIT_TESTING
#include "Launching/PLUnitTesting.h"
#endif // UNIT_TESTING

// ====================
// Application includes
#ifdef APPLICATION_EXECUTION
#include <application/implementation/PLApplication/PLApplication_windows.h>
#endif // APPLICATION_EXECUTION

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

	return 0;
}
