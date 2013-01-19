/*
 * PLCallbackDictionary.cpp
 *
 *  Created on: 13.10.2012
 *      Author: ������
 */
///////////////////////////////////////////////////////////////////////////////
#include "PLReflectionDictionary.h"

///////////////////////////////////////////////////////////////////////////////
PLReflectionDictionary::PLReflectionDictionary()
{
}

PLReflectionDictionary::~PLReflectionDictionary()
{
}

///////////////////////////////////////////////////////////////////////////////
void PLReflectionDictionary::setReflectionForName(PLReflection *inReflection,
		PLString *inName)
{
	reflections[*inName] = inReflection;
}

PLReflection *PLReflectionDictionary::reflectionForName(PLString *inName)
{
	return reflections[*inName];
}
