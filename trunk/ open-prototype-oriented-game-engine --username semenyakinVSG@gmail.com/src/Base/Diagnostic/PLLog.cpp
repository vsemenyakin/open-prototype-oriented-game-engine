#include "PLLog.h"

#include <iostream>
#include "../PLString.h"

#define SEPARATOR "	"
#define GOURP_BEGIN "{"
#define GOURP_END "}"

//////////////////////////////////////////////////////
PLLog::PLLog()
{
	indentation = ref<PLString>::create();
}

PLLog::~PLLog()
{
}

//////////////////////////////////////////////////////
void PLLog::print(const char *inMessage)
{
	std::cout << indentation->getCString() << inMessage << std::endl;
}

void PLLog::beginGroup(const char *inGroupName)
{
	std::cout <<  indentation->getCString() << inGroupName << std::endl;
	std::cout << indentation->getCString() << GOURP_BEGIN << std::endl;
	indentation->append(SEPARATOR);
}

void PLLog::endGroup()
{
	indentation->removeCharacterBack(strlen(SEPARATOR));
	std::cout << indentation->getCString() << GOURP_END << std::endl;
}
