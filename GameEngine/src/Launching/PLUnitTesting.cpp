///////////////////////////////////////////////////////////////////////////////
#include "PLUnitTesting.h"
#include <iostream.h>

#include "UnitTesting/TEST_PLString.h"

///////////////////////////////////////////////////////////////////////////////
PLUnitTesting::PLUnitTesting()
{
	_tests.push_back(new TEST_PLString());
}

PLUnitTesting::~PLUnitTesting()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLUnitTesting::perform()
{
	for (std::list<IPLUnitTest *>::iterator theIterator = _tests.begin();
			theIterator != _tests.end(); ++theIterator)
	{
		(*theIterator)->performTest();
	}

	std::cout << "Unit testing finished..." << std::endl;
}
