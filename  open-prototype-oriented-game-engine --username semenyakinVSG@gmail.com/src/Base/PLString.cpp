#include "PLString.h"
#include "string.h"

PLString::PLString(char *inCString)
{
	//string.append(inCString);
	strcpy(string, inCString);
}

PLString::~PLString()
{

}
