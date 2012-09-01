///////////////////////////////////////////////////////////////////////////////
#include "PLException.h"

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
PLException::PLException(const char *inMessage, int inLineNumber,
		const char *inFileName) throw()
{
	message = inMessage;
	lineNumber = inLineNumber;
	fileName = inFileName;
}

PLException::~PLException() throw()
{
	delete message;
}

///////////////////////////////////////////////////////////////////////////////
const char *PLException::what() const throw()
{
	char *theBuffer = new char[1024];
	sprintf(theBuffer, "[%s:%d] %s", message, lineNumber, fileName);

	return theBuffer;
}
