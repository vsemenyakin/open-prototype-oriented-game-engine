#ifndef PLUNITTESTING_H_
#define PLUNITTESTING_H_

///////////////////////////////////////////////////////////////////////////////
#include "UnitTesting/PLUnitTestCore.h"
#include <list>

///////////////////////////////////////////////////////////////////////////////
class PLUnitTesting
{
private:
	std::list<IPLUnitTest *> _tests;

public:
	PLUnitTesting();
	virtual ~PLUnitTesting();

	void perform();
};

#endif /* PLUNITTESTING_H_ */
