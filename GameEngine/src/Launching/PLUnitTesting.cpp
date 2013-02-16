///////////////////////////////////////////////////////////////////////////////
// Header linking
#include "PLUnitTesting.h"

// Utilities
#include <iostream>

// Tests
#include "UnitTesting/TEST_PLString.h"
#include "UnitTesting/TEST_PL_core_graph.h"
#include "UnitTesting/TEST_PLWindow.h"

///////////////////////////////////////////////////////////////////////////////
PLUnitTesting::PLUnitTesting()
	: _tests()
{
	_tests.push_back(new TEST_PLString());
	_tests.push_back(new TEST_PL_core_graph());
	_tests.push_back(new TEST_PLWindow());
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
