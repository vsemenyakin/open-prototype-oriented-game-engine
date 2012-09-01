

#include "PLArray.h"
#include <list>

PLArray::PLArray(PLIndex inCapasity)
{
	buffer = NULL;

	if (0 != inCapasity)
	{
		buffer = new PLObject *[inCapasity];
	}
}

///////////////////////////////////////////////////////////////////////////////
// *** Content management ***
///////////////////////////////////////////////////////////////////////////////
PLObject *PLArray::objectAtIndex(PLIndex inIndex)
{
	if (inIndex > bufferSize)
	{
		// @@@TODO throw an exception
	}

	return buffer[inIndex];
}

void PLArray::setObjectAtIndex(PLObject *inObject, PLIndex inIndex)
{
	if (inIndex > bufferSize)
	{
		// @@@TODO throw an exception
	}

	PLObject *theElement = buffer[inIndex];
	if (NULL != theElement)
	{
		theElement->release();
	}

	buffer[inIndex] = inObject;
	if (NULL != inObject)
	{
		inObject->retain();
	}
}
