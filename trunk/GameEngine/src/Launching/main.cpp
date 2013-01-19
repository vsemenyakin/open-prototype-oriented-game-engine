///////////////////////////////////////////////////////////////////////////////
using namespace std;

#include "PLApplication.h"
#include "PLUnitTesting.h"

#include <iostream.h>

#define UNIT_TESTING
//#define APPLICATION_EXECUTION

///////////////////////////////////////////////////////////////////////////////

int main()
{
// Unit testing
#ifdef UNIT_TESTING
	PLApplication theApplication;
	theApplication.start();
#endif

// Application execution
#ifdef APPLICATION_EXECUTION
	PLUnitTesting theUnitTesting;
	theUnitTesting.perform();
#endif

	// TODO return here PLError
	return 0;
}
