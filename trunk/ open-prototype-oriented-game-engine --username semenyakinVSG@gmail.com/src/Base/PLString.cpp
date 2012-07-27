#include "PLString.h"

//////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////
const char *PLString::CString()
{
	return theString->c_str();
}

//////////////////////////////////////////////////////////////
void PLString::append(const char *inCString)
{
	theString->append(inCString);
}

void PLString::removeLastSymbles(int inSymblesCount)
{
	theString->resize(theString->size() - inSymblesCount);
}
