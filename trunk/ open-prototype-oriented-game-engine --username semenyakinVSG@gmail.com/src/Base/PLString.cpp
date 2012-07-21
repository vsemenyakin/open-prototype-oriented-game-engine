#include "PLString.h"


PLString::PLString()
{
	theString = new std::string();
}

PLString::PLString(char *inCString)
{
	theString = new std::string(inCString);
}

PLString::~PLString()
{
}

void PLString::append(const char *inCString)
{
	theString->append(inCString);
}
