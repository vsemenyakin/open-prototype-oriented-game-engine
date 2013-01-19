/*
 * PLReflection.cpp
 *
 *  Created on: 13.10.2012
 *      Author: Сергей
 */

///////////////////////////////////////////////////////////////////////////////
#include "PLReflection.h"

#include <iostream.h>

///////////////////////////////////////////////////////////////////////////////
PLReflection::PLReflection(void *inTarget, PLCallback *inCallback)
{
	_callback = inCallback;

	_target = inTarget;
}

PLReflection::PLReflection(PLReflection *inReflection, void *inArgument)
{
	_callback = inReflection->_callback;

	_target = inReflection->_target;
	_argument = inArgument;
}

PLReflection::~PLReflection()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLReflection::setArgument(void *inArgument)
{
	_argument = inArgument;
}

void *PLReflection::getArgument()
{
	return _argument;
}

void PLReflection::call()
{
	_callback(_target, _argument);
}

///////////////////////////////////////////////////////////////////////////////
void dummyReflectionFunction(void *inTarget, void *inArgument)
{
	std::cout << "DUMMY REFLECTION" << std::endl;
}

PLReflection *PLReflection::dummyReflection()
{
	static PLReflection *sReflection = NULL;

	if (NULL == sReflection)
	{
		sReflection = new PLReflection((void *)NULL, dummyReflectionFunction);
	}

	return sReflection;
}
