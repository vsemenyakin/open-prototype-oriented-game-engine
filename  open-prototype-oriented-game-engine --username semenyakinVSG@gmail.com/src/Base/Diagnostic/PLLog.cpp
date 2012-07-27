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
	std::cout << indentation->CString() << inMessage << std::endl;
}

void PLLog::beginGroup(const char *inGroupName)
{
	std::cout <<  indentation->CString() << inGroupName << std::endl;
	std::cout << indentation->CString() << GOURP_BEGIN << std::endl;
	indentation->append(SEPARATOR);
}

void PLLog::endGroup()
{
	indentation->removeLastSymbles(strlen(SEPARATOR));
	std::cout << indentation->CString() << GOURP_END << std::endl;
}
